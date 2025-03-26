// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/DIPickUp.h"
#include "Weapon/TP_PickUpComponent.h"

// Sets default values
ADIPickUp::ADIPickUp()
{
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUpComponent"));
    PickUpComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADIPickUp::BeginPlay()
{
	Super::BeginPlay();

	PickUpComponent->OnPickUp.AddDynamic(this, &ADIPickUp::OnPickUp);

}

void ADIPickUp::OnPickUp(ADiabloIsacCharacter* PickUpCharacter)
{
}

