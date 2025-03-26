// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DIPickUpWeapon.h"
#include "Weapon/TP_PickUpComponent.h"
#include "Manager/DIGameInstance.h"
#include "Weapon/TP_DIWeaponComponent.h"

ADIPickUpWeapon::ADIPickUpWeapon() 
{
	WeaponComponent = CreateDefaultSubobject<UTP_DIWeaponComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(PickUpComponent);
}

void ADIPickUpWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (UDIGameInstance* GameInstance = Cast<UDIGameInstance>(GetGameInstance()))
	{
		WeaponComponent->FireMappingContext = GameInstance->GetWeaponMappingContext();
		WeaponComponent->FireAction = GameInstance->GetWeaponFireAction();
		WeaponComponent->ReloadAction = GameInstance->GetWeaponReloadAction();
		WeaponComponent->SetWeaponData(GameInstance->GetWeaponData("Rifle"));
	}
}

void ADIPickUpWeapon::OnPickUp(ADiabloIsacCharacter* PickUpCharacter)
{

	WeaponComponent->AttachWeapon(PickUpCharacter);
	PickUpCharacter->SetHasWeapon(true);
}
