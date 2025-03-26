// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_DIWeaponComponent.generated.h"

class ADiabloIsacCharacter;
class APlayerController;
class UDIAnimator;
class UDIWeaponData;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIABLOISAC_API UTP_DIWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	class UInputMappingContext* FireMappingContext;

	UPROPERTY()
	class UInputAction* FireAction;

	UPROPERTY()
	class UInputAction* ReloadAction;

	UPROPERTY()
	class UDIWeaponData* WeaponData;

	UFUNCTION()
	void SetWeaponData(UDIWeaponData* Data);

	/** Sets default values for this component's properties */
	UTP_DIWeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool AttachWeapon(ADiabloIsacCharacter* TargetCharacter);

	virtual void Fire();

	int GetMagazineSize()const { return magazineSize; }
	
	int GetAmmoReserve()const { return ammoReserve; }

	void SetAmmoReserve(int ammoReserveSize) { ammoReserve = ammoReserveSize; }

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADI_Projectile> m_projectileActor;

protected:
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void FireShot();
	void StopFire();
	void Reload();
	void FinishReload();

	ADiabloIsacCharacter* Character;
	APlayerController* PlayerController;

	int magazineSize;
	int ammoReserve;
	FTimerHandle FireRateTimerHandle;
	FTimerHandle ReloadTimerHandle;


	bool bIsFiring = false;
	bool bIsReloading = false;

	FVector LastFireDirection;

	UDIAnimator* CharacterAnimator;

};
