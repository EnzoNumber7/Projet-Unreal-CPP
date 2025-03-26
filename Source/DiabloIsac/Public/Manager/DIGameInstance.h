// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Weapon/DIWeaponData.h"
#include "../PowerUp/DA_DIPowerUpData.h"
#include "../Level/DA_DIWaveData.h"
#include "../AI/Enemy.h"
#include "DIGameInstance.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveSpawn, bool, canSpawn );
class WaveManager;

UCLASS()
class DIABLOISAC_API UDIGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDIGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION()
	inline class UInputMappingContext* GetWeaponMappingContext() { return WeaponMappingContext; }

	UFUNCTION()
	inline class UInputAction* GetWeaponFireAction() { return WeaponFireAction; }

	UFUNCTION()
	inline class UInputAction* GetWeaponReloadAction() { return WeaponReloadAction; }

	UFUNCTION()
	inline UDIWeaponData* GetWeaponData(FString name) { return WeaponData.FindRef(name); }

	UFUNCTION()
	inline UDA_DIPowerUpData* GetPowerUpData(FString name) { return PowerUpData.FindRef(name); }

	UFUNCTION()
	inline TArray<UDA_DIWaveData*> GetWaveData()const { return WaveData; }
	
	TSubclassOf<AEnemy> GetEnemyMeleeClass()const { return EnemyMeleeClass; };

	TSubclassOf<AEnemy> GetEnemyRangeClass()const { return EnemyRangeClass; };
	
	void SetNumberZombie();

private:


	UPROPERTY(EditAnywhere, Category = "Wave Management")
	TArray<UDA_DIWaveData*> WaveData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* WeaponMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon ", meta = (AllowPrivateAccess = "true"))
	class UInputAction* WeaponFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon ", meta = (AllowPrivateAccess = "true"))
	class UInputAction* WeaponReloadAction;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TMap<FString, UDIWeaponData*> WeaponData;

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	TMap<FString, UDA_DIPowerUpData*> PowerUpData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemy> EnemyMeleeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemy> EnemyRangeClass;

	WaveManager* waveManager;

};
