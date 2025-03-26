// Fill out your copyright notice in the Description page of Project Settings.


#include "PrincipalMenuGameMod.h"
#include "PrincipalMenu.h"

APrincipalMenuGameMod::APrincipalMenuGameMod()
{
}

void APrincipalMenuGameMod::BeginPlay()
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