// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/DIPickUpPowerUp.h"
#include "Manager/DIGameInstance.h"
#include "PowerUp/DA_DIPowerUpData.h"
#include "GameFramework/Actor.h"
#include "DiabloIsac/DiabloIsacCharacter.h"

ADIPickUpPowerUp::ADIPickUpPowerUp() {
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	Mouv = false;
	// Initialisation des variables
	MoveSpeed = 30.0f;      // Vitesse de déplacement (en unités Unreal par seconde)
	MoveDirection = 1.0f;    // Commence par monter
	MaxHeight = 100.0f;      // Hauteur maximale
	MinHeight = 70.0f;      // Hauteur minimale
}

void ADIPickUpPowerUp::BeginPlay()
{
    Super::BeginPlay();
    if (UDIGameInstance* GameInstance = Cast<UDIGameInstance>(GetGameInstance()))
    {
        Data = Cast<UDA_DIPowerUpData>(GameInstance->GetPowerUpData(Name));
        if (Data)
            MeshComponent->SetStaticMesh(Data->Mesh);
    }
}

void ADIPickUpPowerUp::Initialize()
{
    if (UDIGameInstance* GameInstance = Cast<UDIGameInstance>(GetGameInstance()))
    {
        Data = Cast<UDA_DIPowerUpData>(GameInstance->GetPowerUpData(Name));
        if (Data)
            MeshComponent->SetStaticMesh(Data->Mesh);
    }
}

void ADIPickUpPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// on every frame change rotationg for a smooth rotating actor
	FRotator NewRotation = FRotator(0.f, 2.f, 0.f);
	FVector NewLocation = FVector(0.f, 0.f, 10.f);

	FTransform currentTransform = GetActorTransform();

	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

	// Obtenir la position actuelle
	FVector CurrentLocation = GetActorLocation();

	// Modifier la hauteur
	CurrentLocation.Z += MoveSpeed * MoveDirection * DeltaTime;

	// Vérifier si on a atteint une limite et inverser la direction
	if (CurrentLocation.Z >= MaxHeight)
	{
		MoveDirection = -1.0f; // Descendre
	}
	else if (CurrentLocation.Z <= MinHeight)
	{
		MoveDirection = 1.0f; // Monter
	}

	// Appliquer la nouvelle position
	SetActorLocation(CurrentLocation);
}

void ADIPickUpPowerUp::OnPickUp(ADiabloIsacCharacter* PickUpCharacter)
{
	Data->OnPickup(PickUpCharacter);

	this->Destroy();
}