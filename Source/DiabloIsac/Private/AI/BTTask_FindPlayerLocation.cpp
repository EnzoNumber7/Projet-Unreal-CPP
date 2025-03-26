// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find Player Location";
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsNotStatic") && OwnerComp.GetBlackboardComponent()->GetValueAsBool("IsPlayerInRange"))
	{
		return EBTNodeResult::Succeeded;
	}

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!player)
		return EBTNodeResult::Failed;

	FVector playerLocation = player->GetActorLocation();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", playerLocation);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}