// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/DIMusicPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADIMusicPlayer::ADIMusicPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADIMusicPlayer::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(this, SoundToPlay);
	
}

// Called every frame
void ADIMusicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

