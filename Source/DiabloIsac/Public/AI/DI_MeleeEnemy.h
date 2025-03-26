// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemy.h"
#include "DI_MeleeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API ADI_MeleeEnemy : public AEnemy
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* m_rightHandCollisionBox;

public:
	ADI_MeleeEnemy();

	virtual void Tick(float DeltaTime) override;

	void Attack_Implementation() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void AttackDelay() override;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	
};
