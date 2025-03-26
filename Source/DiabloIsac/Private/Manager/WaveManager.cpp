// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WaveManager.h"
#include "NavModifierVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Manager/DIGameInstance.h"
#include "../DiabloIsacCharacter.h"
#include "NavigationSystem.h"


WaveManager::WaveManager()
{
}

WaveManager::~WaveManager()
{
    if (GameInstance->GetWorld())
    {
        GameInstance->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }

    GameInstance = nullptr; 

}

void WaveManager::Init(UDIGameInstance* gameInstance)
{
	GameInstance = gameInstance;
	WaveData = GameInstance->GetWaveData();
    EnemyMeleeClass = GameInstance->GetEnemyMeleeClass();
    EnemyRangeClass = GameInstance->GetEnemyRangeClass();
    numberZombieWave = 0;
    currentWave = 0;
    isLastWave = false;
}


void WaveManager::InitFirstWave()
{
	FTimerHandle timerHandle;

	GameInstance->GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]() { WaitSpawn(); }, 5.f, false);
}

void WaveManager::InitWave()
{
    if (WaveData[currentWave]->WaveNumber == WaveData.Num()) {
        isLastWave = true;
    }



	if (WaveData[currentWave]->DestroyObstacles.Num() > 0) {
		for (int i = 0; i < WaveData[currentWave]->DestroyObstacles.Num(); i++) {
			WaveData[currentWave]->DestroyObstacles[i]->Destroy();
		}
	}


	if (WaveData[currentWave]->Area.IsValid()) {
		ANavModifierVolume* NavVolume = WaveData[currentWave]->Area.Get();
		if (NavVolume)
		{
			NavVolume->Destroy();
			WaveData[currentWave]->Area.Reset();
		}
	}

	FTimerHandle timerHandle;


	GameInstance->GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]() { WaitSpawn(); }, 5.f, false);
}

void WaveManager::SpawnEnemies()
{
    if (!GameInstance->GetWorld()) return;

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GameInstance->GetWorld(), 0);
    if (!PlayerCharacter)
    {
        return;
    }

    FVector PlayerLocation = PlayerCharacter->GetActorLocation();
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GameInstance->GetWorld());

    if (!NavSystem)
    {
        return;
    }

    for (int i = 0; i < WaveData[currentWave]->NumberMeleeZombie; ++i)
    {
        FVector SpawnLocation;
        bool bFoundValidLocation = false;

        for (int Attempts = 0; Attempts < 10; ++Attempts)
        {
            FVector RandomPoint = PlayerLocation + UKismetMathLibrary::RandomUnitVector() * FMath::RandRange(WaveData[currentWave]->MinRange, WaveData[currentWave]->MaxRange);
            FNavLocation NavLocation;

            if (NavSystem->GetRandomPointInNavigableRadius(RandomPoint, 300.0f, NavLocation))
            {
                SpawnLocation = NavLocation.Location;
                bFoundValidLocation = true;
                break;
            }
        }

        if (bFoundValidLocation)
        {
            ZombieSpawns.Add(SpawnLocation);
            ZombieTypes.Add(EnemyMeleeClass);
        }
    }

    for (int i = 0; i < WaveData[currentWave]->NumberRangeZombie; ++i)
    {
        FVector SpawnLocation;
        bool bFoundValidLocation = false;

        for (int Attempts = 0; Attempts < 10; ++Attempts)
        {
            FVector RandomPoint = PlayerLocation + UKismetMathLibrary::RandomUnitVector() * FMath::RandRange(WaveData[currentWave]->MinRange, WaveData[currentWave]->MaxRange);
            FNavLocation NavLocation;

            if (NavSystem->GetRandomPointInNavigableRadius(RandomPoint, 300.0f, NavLocation))
            {
                SpawnLocation = NavLocation.Location;
                bFoundValidLocation = true;
                break;
            }
        }

        if (bFoundValidLocation)
        {
            ZombieSpawns.Add(SpawnLocation);
            ZombieTypes.Add(EnemyRangeClass);
        }
    }

    GameInstance->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, [this]() { SpawnNextZombie(); }, WaveData[currentWave]->SpawnInterval, true);

}

void WaveManager::SpawnNextZombie()
{
    if (ZombieSpawns.Num() == 0) return;



    if (IndexZombie == ZombieSpawns.Num()) {
        IndexZombie = 0;
        ZombieSpawns.Empty();
        ZombieTypes.Empty();
        GameInstance->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }



    if (GameInstance->GetWorld()->SpawnActor<AEnemy>(ZombieTypes[IndexZombie], ZombieSpawns[IndexZombie], FRotator::ZeroRotator)) {
        numberZombieWave++;

    }
    IndexZombie++;
}

void WaveManager::SetNumberZombie()
{
    numberZombieWave--;
    if (numberZombieWave == 0) {


        if (isLastWave) {
            APlayerController* PlayerController = GameInstance->GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                ADiabloIsacCharacter* character = Cast<ADiabloIsacCharacter>(PlayerController->GetPawn());
                character->OnPlayerEnd.Broadcast(true);
            }
            
        }
        if (currentWave > WaveData.Num() - 1)return;
        InitWave();
    }
}


void WaveManager::WaitSpawn()
{
	SpawnEnemies();
	currentWave++;
}
