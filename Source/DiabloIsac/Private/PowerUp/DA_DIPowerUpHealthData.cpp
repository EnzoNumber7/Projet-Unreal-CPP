// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp/DA_DIPowerUpHealthData.h"
#include "DiabloIsac/DiabloIsacCharacter.h"

void UDA_DIPowerUpHealthData::OnPickup(ACharacter* Target)
{
	ADiabloIsacCharacter* Character = Cast<ADiabloIsacCharacter>(Target);
	if (!Character)return;
	Character->ReceiveHealing(HealAmount);
}
