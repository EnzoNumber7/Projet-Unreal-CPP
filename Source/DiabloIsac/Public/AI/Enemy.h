// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DI_CombatInterface.h"
#include "../Interface/IDamageable.h"
#include "Animation/AnimMontage.h"
#include "Enemy.generated.h"



UCLASS()
class DIABLOISAC_API AEnemy : public ACharacter, public IDI_CombatInterface, public IIDamageable
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	int EnemyHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool m_isNotStatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drop")
	TSubclassOf<class ADIPickUpPowerUp> m_drops;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drop")
	TArray<int> m_spawnProbability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drop")
	TArray<FString> m_dropType;

public:
	// Sets default values for this character's properties
	AEnemy();

	UBehaviorTree* GetBehaviorTree();
	UAnimMontage* GetMontage();
	bool MontageHasFinished();
	float GetAttackRange();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack_Implementation() override;

	void TakeDamage(float DamageAmount) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void AttackDelay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* m_animMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_attackAnimDelay;

	bool m_canAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_damage;

	UFUNCTION()
	void BonusSpawnOnDeath();

};
