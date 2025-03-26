// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/DIGameMode.h"
#include "UI/WDG_DIHUD.h"


ADIGameMode::ADIGameMode()
{
}

void ADIGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (WidgetClass)
    {
        WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport();
        }
    }
}