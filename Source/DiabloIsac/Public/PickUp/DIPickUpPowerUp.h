// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp/DIPickUp.h"
#include "DIPickUpPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API ADIPickUpPowerUp : public ADIPickUp
{
	GENERATED_BODY()
	
public:
	ADIPickUpPowerUp();

	UPROPERTY(EditAnywhere, Category = "Type")
	FString Name;

	void Initialize();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void OnPickUp(class ADiabloIsacCharacter* PickUpCharacter)override;

	UStaticMeshComponent* MeshComponent;

	class UDA_DIPowerUpData* Data;

	float currentTime;
	bool Mouv;

	// Variables pour gérer le mouvement
	float MoveSpeed;         // Vitesse de déplacement
	float MoveDirection;     // Direction du mouvement (1 = haut, -1 = bas)
	float MaxHeight;         // Hauteur maximale
	float MinHeight;         // Hauteur minimale

};
