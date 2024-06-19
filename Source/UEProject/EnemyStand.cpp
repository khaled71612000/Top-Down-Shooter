// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStand.h"

// Sets default values
AEnemyStand::AEnemyStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = 100;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
}

// Called when the game starts or when spawned
void AEnemyStand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyStand::TakeDamage() {
	health -= 20;
	if (health <= 0) {
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(health));
}

