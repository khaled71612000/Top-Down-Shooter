// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeaponPickUp.h"

// Sets default values
AMyWeaponPickUp::AMyWeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	active = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void AMyWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyWeaponPickUp::Interacted() {
	active = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

bool AMyWeaponPickUp::GetActive() {
	return active;
}

