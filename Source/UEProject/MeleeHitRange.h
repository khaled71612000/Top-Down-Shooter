// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EnemyStand.h"
#include "EnemyMove.h"

#include "MeleeHitRange.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API AMeleeHitRange : public ATriggerBox
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	AMeleeHitRange();

	//to access from blueprint , must have two arugments to add dynamc funcntion
	UFUNCTION()
		void Attack(class AActor* overlappedActor , class AActor* otherActor);

	UPROPERTY()
		bool attacking;
};
