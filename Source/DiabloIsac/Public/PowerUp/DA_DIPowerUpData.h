// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_DIPowerUpData.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UDA_DIPowerUpData : public UDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMesh* Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	
	virtual void OnPickup(ACharacter* Target);

};
