// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DIABLOISAC_API IIDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TakeDamage(float DamageAmount) = 0;
};
