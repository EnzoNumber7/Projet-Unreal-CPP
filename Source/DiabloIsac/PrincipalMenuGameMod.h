// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PrincipalMenuGameMod.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API APrincipalMenuGameMod : public AGameModeBase
{
	GENERATED_BODY()
protected:
    APrincipalMenuGameMod();
    virtual void BeginPlay()override;

public:
    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<class UUserWidget> WidgetClass;

    UPROPERTY()
    UUserWidget* WidgetInstance;
};
