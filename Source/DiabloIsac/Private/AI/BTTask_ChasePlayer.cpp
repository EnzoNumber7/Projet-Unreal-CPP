// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChasePlayer.h" 
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIEnemyController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Chase Player"; 
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsNotStatic") && OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsPlayerInRange"))
	{
		return EBTNodeResult::Succeeded;
	}

	AAIEnemyController* enemyController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (!enemyController)
		return EBTNodeResult::Failed;

	APawn* pawn = enemyController->GetPawn();

	UCharacterMovementComponent* enemyMovement = Cast<UCharacterMovementComponent>(pawn->GetMovementComponent());
	enemyMovement->MaxWalkSpeed = m_chaseSpeed;

	FVector playerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(enemyController, playerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;

}