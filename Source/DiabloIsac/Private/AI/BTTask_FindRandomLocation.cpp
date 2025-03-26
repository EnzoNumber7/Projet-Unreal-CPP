// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindRandomLocation.h"
#include "AI/AIEnemyController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* enemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (!enemyController)
		return EBTNodeResult::Failed;

	APawn* pawn = enemyController->GetPawn();

	UCharacterMovementComponent* enemyMovement =  Cast<UCharacterMovementComponent>(pawn->GetMovementComponent());
	enemyMovement->MaxWalkSpeed = m_patrolSpeed;

	FVector origin = pawn->GetActorLocation();

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!navSystem)
		return EBTNodeResult::Failed;

	FNavLocation point;
	if (navSystem->GetRandomPointInNavigableRadius(origin, m_searchRadius, point))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), point.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}