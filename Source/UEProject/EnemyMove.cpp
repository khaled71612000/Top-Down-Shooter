// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMove.h"
#include "Components/BoxComponent.h"
//#include "Perception/AIPerceptionComponent.h"
//#include "Perception/AISenseConfig_Sight.h"
#include "UEProjectCharacter.h"

// Sets default values
AEnemyMove::AEnemyMove()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Col"));
	DamageCollision->SetupAttachment(RootComponent);

	//AIPerComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	//SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	////SightConfig->SightRadius = 1250.f;
	////SightConfig->LoseSightRadius = 1280.f;
	////SightConfig->PeripheralVisionAngleDegrees = 90.f;
 //   SightConfig->SightRadius = 5000.f;
	//SightConfig->LoseSightRadius = 5030.f;
	//SightConfig->PeripheralVisionAngleDegrees = 360.f;

	//SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	//SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	//SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	////deteced actor when will he be forgoton
	//SightConfig->SetMaxAge(0.1f);

	//AIPerComp->ConfigureSense(*SightConfig);

	////if u have multiple sense , set dominant
	//AIPerComp->SetDominantSense(SightConfig->GetSenseImplementation());
	//AIPerComp->OnPerceptionUpdated.AddDynamic(this, &AEnemyMove::OnSensed);
	CurrentVelocity = FVector::ZeroVector;
	MovementSpeed = 275.f;
	////it can be a big number
	//DistanceSquared = BIG_NUMBER;

}

// Called when the game starts or when spawned
void AEnemyMove::BeginPlay()
{
	Super::BeginPlay();
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyMove::OnHit);

	//BaseLocation = this->GetActorLocation();
	CurrentVelocity = FVector::OneVector * MovementSpeed;


}

// Called every frame
void AEnemyMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//keep updated new location 
	//if (!CurrentVelocity.IsZero()) {
	//	NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
	//	//if u are going back and distance is safe and lower than intal value
	//	//update it , if not then reset
	//	if (BackToBaseLocation) {
	//		if ((NewLocation - BaseLocation).SizeSquared2D() < DistanceSquared) {
	//			DistanceSquared = (NewLocation - BaseLocation).SizeSquared2D();
	//		}
	//		else {
	//			CurrentVelocity = FVector::ZeroVector;
	//			DistanceSquared = BIG_NUMBER;
	//			BackToBaseLocation = false;

	//			SetNewRotation(GetActorForwardVector(), GetActorLocation());
	//		}
	//	}
	//	SetActorLocation(NewLocation);
	//}
}

// Called to bind functionality to input
void AEnemyMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyMove::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AUEProjectCharacter* chara = Cast<AUEProjectCharacter>(OtherActor);

	if (chara) {
		chara->DealDamage(DamageValue);
	}
}

//void AEnemyMove::OnSensed(const TArray<AActor*>& UpdatedActors)
//{
//	for (int i = 0; i < UpdatedActors.Num(); i++) {
//		//get information about sensed actor 
//		FActorPerceptionBlueprintInfo info;
//
//		//loop thorugh actors and return information 
//		AIPerComp->GetActorsPerception(UpdatedActors[i], info);
//
//		//if we sensed the last actor was sensed then get hs locaton and get new location
//		if (info.LastSensedStimuli[0].WasSuccessfullySensed()) {
//			FVector dir = UpdatedActors[i]->GetActorLocation() - GetActorLocation();
//			dir.Z = 0.f;
//			//get a safe length of vector and multiply it with speed 
//			CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
//
//			SetNewRotation(UpdatedActors[i]->GetActorLocation(), GetActorLocation());
//
//		}
//		else {
//			//return to normal location if not 
//			FVector dir = BaseLocation - GetActorLocation();
//			dir.Z = 0.f;
//
//			//get squared distance between two points
//			if (dir.SizeSquared2D() > 1.f)
//			{
//				CurrentVelocity = dir.GetSafeNormal() * MovementSpeed;
//				BackToBaseLocation = true;
//
//				SetNewRotation(BaseLocation, GetActorLocation());
//			}
//		}
//	}
//}

//void AEnemyMove::SetNewRotation(FVector TargetPosition, FVector CurrentPos)
//{
//	
//	//get drection and zero t 
//	FVector NewDirecton = TargetPosition - CurrentPos;
//	NewDirecton.Z = 0.0f;
//
//	//set enemy roation to the rotation of new directon
//	EnemyRotation = NewDirecton.Rotation();
//	//set actor roation to the new fvalue
//	SetActorRotation(EnemyRotation);
//}

void AEnemyMove::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f) {
		//Destroy();
	}
}

void AEnemyMove::TakeDamage() {
	Health -= 50;
	if (Health <= 0) {
		//Destroy();
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(Health));
}