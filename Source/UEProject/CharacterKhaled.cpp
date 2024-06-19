// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterKhaled.h"
#include "Bullet.h"
// Sets default values
ACharacterKhaled::ACharacterKhaled()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//controller dont move, camera move
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//move character to drection he is moving
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.f);
	GetCharacterMovement()->AirControl = 0.2f;

	//create spring and make spring on root
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	//how far camera is away
	CameraBoom->TargetArmLength = 300.f;
	//rotate arm based on control
	CameraBoom->bUsePawnControlRotation = true;
	//make camera and set aattack on boom
	//let spring componet control it 
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//already on boom
	FollowCamera->bUsePawnControlRotation = false;

}
void ACharacterKhaled::shoot()
{
	//give him higher pos by 100 after putting him n playerloc , but will spawn under cause nacurate, instaed
	FTransform SpawnTransform = GetActorTransform();
	//SpawnTransform.TransformPosition(FVector(0.f, 0.f, 100.f));
	//SpawnTransform.SetLocation(FollowCamera->GetComponentRotation().Vector() * 200.f + GetActorLocation());

	SpawnTransform.SetLocation(GetActorLocation() + GetActorForwardVector() * 50);

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<ABullet>(BulletBP, SpawnTransform, SpawnParams);
	UE_LOG(LogTemp, Warning, TEXT("Bang BANG"));
}
// Called when the game starts or when spawned
void ACharacterKhaled::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterKhaled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterKhaled::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ACharacterKhaled::shoot);
	//control yawroation a function n apawn
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterKhaled::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterKhaled::AddControllerPitchInput);

	//jump already in our character
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterKhaled::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterKhaled::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterKhaled::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterKhaled::MoveRight);

}

void ACharacterKhaled::MoveForward(float Axis) {

	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);

}
void ACharacterKhaled::MoveRight(float Axis) {
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}