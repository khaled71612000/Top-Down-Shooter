// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPawn.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathVectorCommon.h"
#include <UEProject/Bomb.h>

// Sets default values
APotatoPawn::APotatoPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APotatoPawn::HandleBombPlace()
{
	GetWorld()->SpawnActor<ABomb>(ABomb::StaticClass(), GetActorLocation() + GetActorForwardVector() * 50, FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void APotatoPawn::BeginPlay()
{
	Super::BeginPlay();
	OurRoot = NewObject<USceneComponent>(this, USceneComponent::StaticClass());
	if (OurRoot) {
		OurRoot->RegisterComponent();
		SetRootComponent(OurRoot);
	}
	UE_LOG(LogTemp, Warning, TEXT("This Is A Bag "));
}

void APotatoPawn::HandleMoveForward(float inputVal)
{
	MoveInput.X = inputVal;
}

void APotatoPawn::HandleMoveRight(float inputVal)
{
	MoveInput.Y = inputVal;

}

void APotatoPawn::HandleMoveYawInput(float inputVal)
{
	AddControllerYawInput(inputVal);
}

void APotatoPawn::HandleMovePitchInput(float inputVal)
{
	AddControllerPitchInput(inputVal);
}

// Called every frame
void APotatoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float controlYaw = GetControlRotation().Yaw;
	FRotator CurrentActorRot = GetActorRotation();

	CurrentActorRot.Yaw = controlYaw;
	SetActorRotation(CurrentActorRot);

	FVector ForwardMovement = GetActorForwardVector() * MoveInput.X * Speed1 * DeltaTime;
	FVector RightMovement = GetActorRightVector() * MoveInput.Y * Speed1 * DeltaTime;
	SetActorLocation(GetActorLocation() + ForwardMovement + RightMovement);

	DrawDebugSphere(GetWorld(), GetActorLocation(), 100, 12, FColor::Red, false, 0.1f);

	FVector EyeLoc;
	FRotator EyeRot;


	GetController()->GetPlayerViewPoint(EyeLoc, EyeRot);
	DrawDebugLine(GetWorld(), EyeLoc, EyeLoc + EyeRot.Vector() * 200, FColor::Cyan, false, -1, 1, 20);

}

// Called to bind functionality to input
void APotatoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APotatoPawn::HandleMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APotatoPawn::HandleMoveRight);
	PlayerInputComponent->BindAxis("YawInput", this, &APotatoPawn::HandleMoveYawInput);
	PlayerInputComponent->BindAxis("PitchInput", this, &APotatoPawn::HandleMovePitchInput);
	PlayerInputComponent->BindAction("PlaceBomb", EInputEvent::IE_Released, this, &APotatoPawn::HandleBombPlace);
}

