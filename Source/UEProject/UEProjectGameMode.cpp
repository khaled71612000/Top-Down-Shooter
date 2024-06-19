// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEProjectGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"

AUEProjectGameMode::AUEProjectGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	EnemiesN = 0;

}

void AUEProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	//courtoine , repeat every sec to load a sec and to cancle use func
	/*GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &AUEProjectGameMode::CountDownTimer,
		1.0f, true, 1.0f);*/
	spawnEnemy();
}
void AUEProjectGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	CheckWin();
}

void AUEProjectGameMode::CheckWin() {

		////EngineUtils.h
		//for (TActorIterator<AEnemyMove> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		//{
		//	Wave++;
		//}
	TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyMove::StaticClass(), FoundActors);
	EnemyAlive = FoundActors.Num();
	if (FoundActors.Num() == 0) {

		RestartGamePlay(true);
	}

//for (AActor* TActor: FoundActors)
//{
//	AEnemyMove* MyActor = Cast<AEnemyMove>(TActor);
//
//	if (MyActor != nullptr)
//	{
//	}
//}
}



void AUEProjectGameMode::spawnEnemy()
{
	 EnemiesN = FMath::RandRange(2,4);
	 int32 nspawn = EnemiesN;

	for (int i = 0; i < nspawn; i++) {
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0, 0, 0);

	 GetWorld()->SpawnActor(Enemy , &SpawnPosition,&SpawnRotation);
	}
	if (Wave != 3) {
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
				float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
				float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

				FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
				FRotator SpawnRotation = FRotator(0, 0, 0);

				GetWorld()->SpawnActor(Enemy, &SpawnPosition, &SpawnRotation);
				GetWorld()->SpawnActor(Enemy, &SpawnPosition, &SpawnRotation);
				GetWorld()->SpawnActor(Enemy, &SpawnPosition, &SpawnRotation);

			
		}, 5, false);
	}
}


void AUEProjectGameMode::RestartGamePlay(bool Won)
{
	if (Won) {
		if (Wave != 3) {
		Wave++;
		spawnEnemy();
		}
		else {
			isGameWon = true;
		}
	}
	else {
		//reset after 3 seconds if lost
		/*FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this,
			&AUEProjectGameMode::ResetLevel, 3.f);*/
		isGameLost = true;
	}
}
void AUEProjectGameMode::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Gameplay");

}

//void AUEProjectGameMode::CountDownTimer()
//{
//	TimerCount--;
//
//	if (TimerCount == 0) {
//		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
//		ResetLevel();
//	}
//}

