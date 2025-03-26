// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AAIEnemyController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class UAISenseConfig_Sight* m_sightConfig;

	void SetupPerceptionSystem();

 	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);
};
