// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/DIGameInstance.h"
#include "NavModifierVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "../DiabloIsacCharacter.h"
#include "Manager/WaveManager.h"
#include "NavigationSystem.h"

UDIGameInstance::UDIGameInstance() {
    
    waveManager = new WaveManager();

}

void UDIGameInstance::Init() {
	Super::Init();



	WaveData.Reserve(4);
    waveManager->Init(this);
    waveManager->InitFirstWave();

}

void UDIGameInstance::Shutdown() {
    Super::Shutdown();

    delete waveManager;
}

void UDIGameInstance::SetNumberZombie(){

    waveManager->SetNumberZombie();

}

