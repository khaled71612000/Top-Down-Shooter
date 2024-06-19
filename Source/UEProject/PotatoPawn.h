// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PotatoPawn.generated.h"

UCLASS()
class UEPROJECT_API APotatoPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APotatoPawn();
	void HandleBombPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector MoveInput;
	float Speed1 = 80;
	float Speed2 = 100;
	USceneComponent* OurRoot;

	void HandleMoveForward(float inputVal);
	void HandleMoveRight(float inputVal);
	void HandleMoveYawInput(float inputVal);
	void HandleMovePitchInput(float inputVal);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
