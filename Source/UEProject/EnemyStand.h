// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "EnemyStand.generated.h"

UCLASS()
class UEPROJECT_API AEnemyStand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyStand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TakeDamage();

	UPROPERTY()
		int health;
	UPROPERTY(VisibleAnywhere, Category = "MeshDamage")
		class UStaticMeshComponent* mesh;


};
