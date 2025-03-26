// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DI_BTTask_Attack.h"
#include "AI/AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

UDI_BTTask_Attack::UDI_BTTask_Attack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UDI_BTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey()))
	{
		return EBTNodeResult::Failed;
	}

	AAIEnemyController* controller = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	AEnemy* enemy = Cast<AEnemy>(controller->GetPawn());

	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsNotStatic"))
	{
		controller->StopMovement();
	}
	IDI_CombatInterface* icombat = Cast<IDI_CombatInterface>(enemy);

	if (enemy->MontageHasFinished())
	{
		icombat->Execute_Attack(enemy);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}