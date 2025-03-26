// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp/DIPickUp.h"
#include "DIPickUpWeapon.generated.h"


UCLASS()
class DIABLOISAC_API ADIPickUpWeapon : public ADIPickUp
{
	GENERATED_BODY()

public:
	ADIPickUpWeapon();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UTP_DIWeaponComponent* WeaponComponent;
	

	void OnPickUp(class  ADiabloIsacCharacter* PickUpCharacter)override;
};
