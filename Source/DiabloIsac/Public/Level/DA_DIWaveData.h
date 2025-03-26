// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DA_DIWaveData.generated.h"


class ANavModifierVolume;

UCLASS()
class DIABLOISAC_API UDA_DIWaveData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int WaveNumber;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumberMeleeZombie;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumberRangeZombie;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeBeforeNextWave;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSoftObjectPtr<AStaticMeshActor>> DestroyObstacles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<ANavModifierVolume> Area;
};
