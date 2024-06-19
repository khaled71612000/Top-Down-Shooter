// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "UEProjectGameModeBase.cpp"
#include "UEProjectGameMode.h"

#include "Bullet.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include <UEProject/Bomb.h>
#include "GameFramework/SpringArmComponent.h"

#include <UEProject/UEProjectGameMode.h>
//////////////////////////////////////////////////////////////////////////
// AUEProjectCharacter

AUEProjectCharacter::AUEProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	collectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRange"));
	collectionRange->AttachTo(RootComponent);
	collectionRange->SetSphereRadius(100.f);
	health = 100;

	LoadedAmmo = 10;
	ammoPool = 100;

}
void AUEProjectCharacter::HandleBombPlace()
{
	FTimerHandle TimerHandle;

			TArray<FHitResult> OutHits;

			FVector SweepStart = GetActorLocation();
			FVector SweepEnd = GetActorLocation();
			SpawnRotation = GetControlRotation();
			SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50;
			FTransform SpawnTransform = GetActorTransform();
			SpawnTransform.SetLocation(SpawnLocation);
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;


			GetWorld()->SpawnActor<ABomb>(BombShape, SpawnTransform, SpawnParams);
			FCollisionShape MyColSphere = FCollisionShape::MakeSphere(200.f);

			DrawDebugSphere(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Green, false, 1);
			if (BombSound) {
				UGameplayStatics::PlaySoundAtLocation(this, BombSound, SpawnTransform.GetLocation());
			}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{

			bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, COLLISION_SHOT, MyColSphere);

			if (isHit)
			{
				// loop through TArray
				for (auto& Hit : OutHits)
				{
					if (GEngine)
					{
						if (Hit.Actor.Get()) {
							Hit.Actor->Destroy();
							
						}

					}
				}
			}
		}, 3, false);



}

void AUEProjectCharacter::BeginPlay() {
	Super::BeginPlay();
	//if u assigned a melesocket 
	//attacth to compopnment a pivot poitn where scale doesnt matter 
	if (MeleeAttack) {
		MeleeAttack->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("MeleSocket"));
	}

	if (wielded) {
		wielded->SetActorHiddenInGame(true);
	}
	world = GetWorld();
	AnimInstance = GetMesh()->GetAnimInstance();
	health = 100;

}

void AUEProjectCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (hitBox && hitBox->attacking) {
		if (GetMesh()->IsPlaying() == true) {
			hitBox->attacking = false;

		}
	}

}


//////////////////////////////////////////////////////////////////////////
// Input

void AUEProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUEProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUEProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUEProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUEProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUEProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUEProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUEProjectCharacter::OnResetVR);
	PlayerInputComponent->BindAction("Hit", IE_Pressed, this, &AUEProjectCharacter::Attack);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AUEProjectCharacter::Interact);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AUEProjectCharacter::shoot);
	PlayerInputComponent->BindAction("Bomb", EInputEvent::IE_Released, this, &AUEProjectCharacter::HandleBombPlace);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AUEProjectCharacter::OnReload);

}

void AUEProjectCharacter::Interact() {
	TArray<AActor*> inRangeItems;

	//put in list all overalped actors in sphere around player 
	collectionRange->GetOverlappingActors(inRangeItems);

	for (int i = 0; i < inRangeItems.Num(); i++) {
		//try to cast current if so 
		AMyWeaponPickUp* const testItem = Cast<AMyWeaponPickUp>(inRangeItems[i]);
		//check if item is not dead and memory is valid
		if (testItem && !testItem->IsPendingKill() && testItem->GetActive()) {
			testItem->Interacted();
			if (wielded) {
				wielded->SetActorHiddenInGame(false);
				AbleToShoot = true;
			}
		}
		AHealthPickUp* const testItem1 = Cast<AHealthPickUp>(inRangeItems[i]);
		//check if item is not dead and memory is valid
		if (testItem1 && !testItem1->IsPendingKill() && testItem1->GetActive()) {
			testItem1->Interacted();
			health += 30;

			if (health >= 100) {
				health = 100;
			}
		}
	}

}

void AUEProjectCharacter::shoot()
{
	if (AbleToShoot) {


		if (world != NULL) {

			SpawnRotation = GetControlRotation();
			SpawnLocation = GetActorLocation() + GetActorForwardVector() * 150;

			//give him higher pos by 100 after putting him n playerloc , but will spawn under cause nacurate, instaed
			FTransform SpawnTransform = GetActorTransform();
			//SpawnTransform.TransformPosition(FVector(0.f, 0.f, 100.f));
			//SpawnTransform.SetLocation(FollowCamera->GetComponentRotation().Vector() * 200.f + GetActorLocation());

			SpawnTransform.SetLocation(SpawnLocation);

			FActorSpawnParameters SpawnParams;
			//handle if acttors spawn and on collsoin
			SpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			if (LoadedAmmo <= 0) { NeedReload = true; return; }
			LoadedAmmo -= 1;

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),muzzleFlash,SpawnTransform);



			GetWorld()->SpawnActor<ABullet>(BulletBP, SpawnTransform, SpawnParams);
			TArray<FOverlapResult> Overlaps;

			GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, COLLISION_SHOT, FCollisionShape::MakeSphere(200));
			FRotator rot;
			for (FOverlapResult& Overlap : Overlaps) {
				if (Overlap.Actor.Get()) {
					Overlap.Actor->Destroy();
				}
			}
			if (FireSound != NULL) {
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}
			if (FireAnimation != NULL && AnimInstance != NULL) {
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}
void AUEProjectCharacter::OnReload() {
	NeedReload = false;
	//if u dont have ammo in mag reload
	if (ammoPool <= 0 || LoadedAmmo >= 10) { return; }

	//if we have enough ammo then load ammo
	if (ammoPool < (10 - LoadedAmmo)) {
		LoadedAmmo = LoadedAmmo + ammoPool;
		ammoPool = 0;
	}
	else {
		ammoPool = ammoPool - (10 - LoadedAmmo);
		LoadedAmmo = 10;
	}
	if (reloadAnim != NULL) {
		AnimInstance->Montage_Play(reloadAnim, 2.1f);
	}
}

void AUEProjectCharacter::DealDamage(float DamageAmount)
{
	health -= DamageAmount;

	if (health <= 0.0f) {
		//RestartGame

		AUEProjectGameMode* MyGameMode =
			Cast<AUEProjectGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		
		if (MyGameMode) {
			MyGameMode->RestartGamePlay(false);
		}
		
		//Destroy();
	}
}

void AUEProjectCharacter::Attack() {
	if (Hit) {
		//When Attack Do an animation to mesh

		//GetMesh()->SetAnimation(Hit);

		//Dont Loop and play once
		/*GetMesh()->PlayAnimation(Hit, false);
		FTimerHandle ExplosionTimerHandle;

		GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &AUEProjectCharacter::restartAnim, 1.2f, false);*/
		if (FireAnimation != NULL && AnimInstance != NULL) {
			AnimInstance->Montage_Play(Hit, 1.f);
		}
		if (FireSound != NULL) {
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}
		if (hitBox) {
			hitBox->attacking = true;
			SetActorLocation(this->GetActorLocation() + GetActorForwardVector() * -15);
		}

		
	}
	/*	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("AnimBlueprint'/Game/ParagonWraith/Characters/Heroes/Wraith/Wraith_AnimBlueprint.Wraith_AnimBlueprint'"));

		GetMesh()->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);*/
}

//void AUEProjectCharacter::restartAnim() {
//	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
//}

void AUEProjectCharacter::OnResetVR()
{
	// If UEProject is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in UEProject.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUEProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AUEProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AUEProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUEProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUEProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUEProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
