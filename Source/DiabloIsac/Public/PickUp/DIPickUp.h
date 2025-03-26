// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DIPickUp.generated.h"

UCLASS()
class DIABLOISAC_API ADIPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADIPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UTP_PickUpComponent* PickUpComponent;

	UFUNCTION()
	virtual void OnPickUp(class  ADiabloIsacCharacter* PickUpCharacter);
};
