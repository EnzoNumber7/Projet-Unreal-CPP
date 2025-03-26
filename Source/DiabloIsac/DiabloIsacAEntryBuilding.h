// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DiabloIsacAEntryBuilding.generated.h"

UCLASS()
class DIABLOISAC_API ADiabloIsacAEntryBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADiabloIsacAEntryBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent * OverlappedComp,
		AActor * OtherActor,
		UPrimitiveComponent * OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult
	);

	UFUNCTION()
	void OnOverlapExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	bool isInBuilding;
	bool isRotate;

	USpringArmComponent* TopDownCamera;

	FRotator currentRotation;
	FRotator afterRotation;

	float currentTime;
};
