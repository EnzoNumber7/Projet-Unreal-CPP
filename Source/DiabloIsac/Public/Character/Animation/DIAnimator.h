// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DIAnimator.generated.h"

/**
 * 
 */

class UCharacterMovementComponent;
class ACharacter;

UCLASS()
class DIABLOISAC_API UDIAnimator : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	bool GetHasRifle()const { return HasRifle; }

	void SetHasRifle(bool HasWeapon) { HasRifle = HasWeapon; }
	void SetIsShooting(bool IsShoot) { IsShooting = IsShoot;  }

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation");
	bool HasRifle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation");
	bool IsShooting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation");
	bool IsMoving;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation");
	float GroundSpeed;

	ACharacter* Character;
	UCharacterMovementComponent* MoveComp;
};
