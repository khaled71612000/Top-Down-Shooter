// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeHitRange.h"

AMeleeHitRange::AMeleeHitRange() {
	OnActorBeginOverlap.AddDynamic(this, &AMeleeHitRange::Attack);

	attacking = false;
}


void AMeleeHitRange::BeginPlay() {
	Super::BeginPlay();
}


void AMeleeHitRange::Attack(class AActor* overlappedActor, class AActor* otherActor) {
	
	//not attackig itself and there is anotehr actor
	if (otherActor && otherActor != this) {
		//try to cast and if so and its attacking take damage
		AEnemyStand* enemy = Cast<AEnemyStand>(otherActor);
		AEnemyMove* enemyTroll = Cast<AEnemyMove>(otherActor);

		if (enemy && attacking) {
			enemy->TakeDamage();
		}
		if (enemyTroll && attacking) {
			enemyTroll->TakeDamage();
		}
	}
}