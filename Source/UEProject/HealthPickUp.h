// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickUp.generated.h"

UCLASS()
class UEPROJECT_API AHealthPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Interacted();
	bool GetActive();

private:
	UPROPERTY()
		bool active;
	UPROPERTY(VisibleAnywhere, Category = "MeshPickUp")
		class UStaticMeshComponent* mesh;
};
