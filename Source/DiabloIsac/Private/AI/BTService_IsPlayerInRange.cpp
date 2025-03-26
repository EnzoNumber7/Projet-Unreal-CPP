// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_IsPlayerInRange.h"
#include "AI/AIEnemyController.h"
#include "AI/Enemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInRange::UBTService_IsPlayerInRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "is Player in Range";
}

void UBTService_IsPlayerInRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* controller = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	AEnemy* enemy = Cast<AEnemy>(controller->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),(enemy->GetDistanceTo(player) <= enemy->GetAttackRange()));
}