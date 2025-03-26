// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI/Enemy.h"
#include "DI_BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UDI_BTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UDI_BTTask_Attack(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
