// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/StaticMeshComponent.h"
#include <Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include "EnemyMove.h"
#include "UEProjectCharacter.h"
#include "UEProjectGameModeBase.cpp"
// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");

	colsphere = CreateDefaultSubobject<USphereComponent>("bulletcol");
	colsphere->InitSphereRadius(20.f);
	SetRootComponent(colsphere);
	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	//who is the projectile moving
	BulletMovement->UpdatedComponent = colsphere;
	BulletMovement->InitialSpeed = 3000.0f;
	BulletMovement->MaxSpeed = 3000.0f;
	//rotate accordng to velociity
	BulletMovement->bRotationFollowsVelocity = true;
	//alow bounce
	//BulletMovement->bShouldBounce = true;
	//destroy if doesnt hit in 3 seconds
	InitialLifeSpan = 3;
}
void AEnemyBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AUEProjectCharacter* Enemy1 = Cast<AUEProjectCharacter>(OtherActor);
	if (Enemy1) {
		Enemy1->DealDamage(DamageValue);
		Destroy();
	}
}
// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	colsphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnHit);

}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

