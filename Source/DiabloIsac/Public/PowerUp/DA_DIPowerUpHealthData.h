// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp/DA_DIPowerUpData.h"
#include "DA_DIPowerUpHealthData.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UDA_DIPowerUpHealthData : public UDA_DIPowerUpData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HealAmount;

	virtual void OnPickup(ACharacter* Target)override;
};
