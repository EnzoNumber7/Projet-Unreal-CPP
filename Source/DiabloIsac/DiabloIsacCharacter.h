// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "public/Interface/IDamageable.h"
#include "DiabloIsacCharacter.generated.h"

class UTP_DIWeaponComponent;
class UDIWeaponData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEnd, bool, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponPickUp, UDIWeaponData*, WeaponData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFire, int, ammo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReload, int, magazineSize, int, ammo);


UCLASS(Blueprintable)
class ADiabloIsacCharacter : public ACharacter,  public IIDamageable
{
	GENERATED_BODY()

public:
	ADiabloIsacCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	bool GetHasWeapon()const { return hasWeapon; }

	void SetHasWeapon(bool playerHasWeapon) { hasWeapon = playerHasWeapon; }

	void TakeDamage(float DamageAmount) override;

	void ReceiveHealing(float HealAmount);

	void SetCharacterSpeed(float speed, float duration);

	void RefillAmmoReserve();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnWeaponPickUp OnWeaponPickUp;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnFire OnWeaponFire;

	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnReload OnWeaponReload;

	UPROPERTY(BlueprintAssignable, Category = "Player")
	FOnPlayerEnd OnPlayerEnd;


	UFUNCTION()
	void ResetWalkSpeed(float walkSpeed);

	float GetPlayerHealth() const { return PlayerCurrentHealth; }

	float GetPlayerMaxHealth() const { return PlayerMaxHealth;  }

	void SetPlayerWeapon(UTP_DIWeaponComponent* weapon);

	UTP_DIWeaponComponent* GetPlayerWeapon()const { return m_weaponComponent; }

	void Fire();
	void Reload();

	void SetIsInBuilding(bool boolean) { isInBuilding = boolean; }
	bool GetIsInBuilding() { return isInBuilding; }

	class USoundBase* SoundToPlay;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float PlayerMaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	class UAIPerceptionStimuliSourceComponent* m_stimulusSource;

	class UTP_DIWeaponComponent* m_weaponComponent;

	void SetupStimulusSource();

	bool hasWeapon;

	float PlayerCurrentHealth;
	bool isInBuilding;
};

