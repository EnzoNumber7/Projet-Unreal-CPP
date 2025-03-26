// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp/DA_DIPowerUpData.h"
#include "DA_DIPowerUpAmmo.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UDA_DIPowerUpAmmo : public UDA_DIPowerUpData
{
	GENERATED_BODY()
	
public:

	virtual void OnPickup(ACharacter* Target)override;
};
