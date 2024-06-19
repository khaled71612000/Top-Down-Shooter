// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyMove.h"
#include "EngineUtils.h"
#include "UEProjectGameMode.generated.h"

UCLASS(minimalapi)
class AUEProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUEProjectGameMode();
	void RestartGamePlay(bool Won);
private:
	void ResetLevel();
//public:
//	UPROPERTY(BlueprintReadOnly)
//		int TimerCount = 300;
//private:
//	FTimerHandle CountDownTimerHandle = FTimerHandle();
//
//	void CountDownTimer();

public:
	 void BeginPlay() ;
	 void Tick(float DeltaTime) ;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemyMove> Enemy;
	float Spawn_Z = 166.5f;
		UPROPERTY(EditAnywhere)
			float Spawn_X_Min;
		UPROPERTY(EditAnywhere)
		    float Spawn_X_Max;
		UPROPERTY(EditAnywhere)
			float Spawn_Y_Min;
		UPROPERTY(EditAnywhere)
			float Spawn_Y_Max;

		void spawnEnemy();
		void SetNewRotation(FVector TargetPosition, FVector CurrentPos);
		UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int32 Wave;
		int32 EnemiesN;
		int32 EnemyAlive;
		UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		bool isGameWon;
		UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		bool isGameLost;
		void CheckWin();
		//void AddWave();
		void SecspawnEnemy();
};



