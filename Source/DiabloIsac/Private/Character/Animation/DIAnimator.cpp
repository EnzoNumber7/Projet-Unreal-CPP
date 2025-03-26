// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/DIAnimator.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UDIAnimator::NativeInitializeAnimation() {

	Super::NativeInitializeAnimation();

	HasRifle = false;
	IsMoving = false;
	GroundSpeed = 0;

	Character = Cast<ACharacter>(TryGetPawnOwner());

	if (!Character) return;
	MoveComp = Character->GetCharacterMovement();
}

void UDIAnimator::NativeUpdateAnimation(float DeltaSeconds) {

	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character) {
		
		Character = Cast<ACharacter>(TryGetPawnOwner());

	}

	if (!Character)return;

	FVector Velocity = MoveComp->Velocity;

	GroundSpeed = FVector(Velocity.X, Velocity.Y, 0.0f).Size();

	IsMoving = Character->GetVelocity().Size2D() > 0 ? true : false;
}

