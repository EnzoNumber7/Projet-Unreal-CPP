// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemy.h"
#include "DI_GunEnemy.generated.h"

/**
 *
 */
UCLASS()
class DIABLOISAC_API ADI_GunEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	ADI_GunEnemy();

	virtual void Tick(float DeltaTime) override;

	void Attack_Implementation() override;

	virtual void AttackDelay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class USoundBase* SoundToPlay;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADI_Projectile> m_projectileActor;

private:
	UPROPERTY()
	class USkeletalMeshComponent* m_characterMesh;

	UPROPERTY()
	class UStaticMeshComponent* m_gunMesh;
};
