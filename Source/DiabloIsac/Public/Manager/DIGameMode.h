// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DIGameMode.generated.h"

/**
 * 
 */

UCLASS()
class DIABLOISAC_API ADIGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ADIGameMode();

	virtual void BeginPlay()override;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY()
	UUserWidget* WidgetInstance;
};
