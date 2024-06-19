// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UEProjectGameModeBase.cpp"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle ExplosionTimerHandle;

	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ABomb::Explode, 2, false);

}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::Explode()
{
	TArray<FOverlapResult> Overlaps;

	FRotator rot;
	GetWorld()->OverlapMultiByChannel(Overlaps, GetActorLocation(), FQuat::Identity, COLLISION_SHOT, FCollisionShape::MakeSphere(200));
	for (FOverlapResult& Overlap : Overlaps) {
		if (Overlap.Actor.Get()) {
			if (BombS) {
				UGameplayStatics::PlaySoundAtLocation(this, BombS, GetActorLocation());
			}
			Overlap.Actor->Destroy();
		}
	}
}