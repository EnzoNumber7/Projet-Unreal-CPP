// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp/DA_DIPowerUpAmmo.h"
#include "DiabloIsac/DiabloIsacCharacter.h"

void UDA_DIPowerUpAmmo::OnPickup(ACharacter* Target)
{
	ADiabloIsacCharacter* Character = Cast<ADiabloIsacCharacter>(Target);
	if (!Character)return;
	Character->RefillAmmoReserve();
}