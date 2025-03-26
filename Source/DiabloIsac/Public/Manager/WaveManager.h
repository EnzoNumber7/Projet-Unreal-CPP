// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Level/DA_DIWaveData.h"
/**
 * 
 */
class AEnemy;
class UDIGameInstance;

class DIABLOISAC_API WaveManager
{
public:
	WaveManager();
	~WaveManager();

	void Init(UDIGameInstance* gameInstance);


	void InitFirstWave();
	void SetNumberZombie();

private:

	void InitWave();
	void SpawnNextZombie();

	void SpawnEnemies();


	TSubclassOf<AEnemy> EnemyMeleeClass;

	TSubclassOf<AEnemy> EnemyRangeClass;

	TArray<UDA_DIWaveData*> WaveData;

	TArray<FVector> ZombieSpawns;
	TArray<TSubclassOf<AEnemy>> ZombieTypes;



	int32 IndexZombie = 0;

	FTimerHandle SpawnTimerHandle;

	UDIGameInstance* GameInstance;

	void WaitSpawn();

	int currentWave;
	int numberZombieWave;

	bool isLastWave;
};
