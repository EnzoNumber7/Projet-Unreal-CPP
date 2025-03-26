// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemy.h"
#include "Components/BoxComponent.h"
#include "DiabloIsac/DiabloIsacCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIEnemyController.h"
#include "TimerManager.h"
#include "AI/DI_GunEnemy.h"
#include "PickUp/DIPickUpPowerUp.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager\DIGameInstance.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	m_canAttack = true;

	AAIEnemyController* controller = Cast<AAIEnemyController>(m_tree->GetOuter());

	if (controller)
	{
		controller->GetBlackboardComponent()->SetValueAsBool("IsStatic", m_isNotStatic);
	}

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* AEnemy::GetBehaviorTree()
{
	return m_tree;
}

UAnimMontage* AEnemy::GetMontage()
{
	return m_animMontage;
}

float AEnemy::GetAttackRange()
{
	return m_attackRange;
}

void AEnemy::Attack_Implementation()
{
}

void AEnemy::TakeDamage(float DamageAmount) {
	EnemyHealth -= DamageAmount;

	if (EnemyHealth <= 0) {
		if (UDIGameInstance* GameInstance = Cast<UDIGameInstance>(GetGameInstance())) {

			GameInstance->SetNumberZombie();
			BonusSpawnOnDeath();
		}
		this->Destroy();
	};

}

void AEnemy::BonusSpawnOnDeath()
{
	int RandomInt = UKismetMathLibrary::RandomIntegerInRange(1, 100);
	int currentProba = 0;

	for (int i = 0; i < m_spawnProbability.Num();i++)
	{

		if (RandomInt <= currentProba + m_spawnProbability[i] && RandomInt > currentProba)
		{
			ADIPickUpPowerUp* drop = GetWorld()->SpawnActor<ADIPickUpPowerUp>(m_drops, GetActorLocation(), GetActorRotation());
			drop->Name = m_dropType[i];
			drop->Initialize();
			return;
		}
		currentProba += m_spawnProbability[i];
	}

}

bool AEnemy::MontageHasFinished()
{
	return GetMesh()->GetAnimInstance()->Montage_GetIsStopped(GetMontage());
}

void AEnemy::AttackDelay()
{
	m_canAttack = true;
}

