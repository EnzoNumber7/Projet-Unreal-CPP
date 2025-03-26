// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_FindRandomLocation(const FObjectInitializer& ObjectInitialiser);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
	float m_searchRadius = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float m_patrolSpeed = 300;

	
};
