// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DIWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UDIWeaponData : public UDataAsset
{
	GENERATED_BODY()
	

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MagazineCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AmmoReserve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ReloadTime;
};
