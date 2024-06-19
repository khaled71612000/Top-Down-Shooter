// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
 void AShooterAI::BeginPlay() {
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn);
	if (AITree != nullptr) {
		RunBehaviorTree(AITree);
	}
}

 void AShooterAI::Tick(float DeltaSeconds) {
	 Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AITree != nullptr) {
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyLocation"), GetTargetLocation(this));
	}
	/* APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	 MoveTo(PlayerPawn);*/
 }

