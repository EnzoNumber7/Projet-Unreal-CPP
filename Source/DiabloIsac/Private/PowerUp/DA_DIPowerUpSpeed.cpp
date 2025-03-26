// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp/DA_DIPowerUpSpeed.h"
#include "DiabloIsac/DiabloIsacCharacter.h"


void UDA_DIPowerUpSpeed::OnPickup(ACharacter* Target)
{
	ADiabloIsacCharacter* Character = Cast<ADiabloIsacCharacter>(Target);
	if (!Character)return;
	Character->SetCharacterSpeed(SpeedFactor, SpeedDuration);
}