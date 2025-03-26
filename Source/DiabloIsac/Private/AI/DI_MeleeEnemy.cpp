// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DI_MeleeEnemy.h"
#include "Components/BoxComponent.h"
#include "DiabloIsac/DiabloIsacCharacter.h"

ADI_MeleeEnemy::ADI_MeleeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	m_rightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Hand Component"));
}

void ADI_MeleeEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (m_rightHandCollisionBox && GetMesh())
	{
		FAttachmentTransformRules const Rules{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			false };

		m_rightHandCollisionBox->AttachToComponent(GetMesh(), Rules, TEXT("RightHandSocket"));
		m_rightHandCollisionBox->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));

		m_rightHandCollisionBox->SetRelativeLocation(FVector(0, -10, 5));
		m_rightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		m_rightHandCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADI_MeleeEnemy::OnBeginOverlap);

	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ADI_MeleeEnemy::OnMontageEnded);
	}
}

void ADI_MeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADI_MeleeEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADiabloIsacCharacter* player = Cast<ADiabloIsacCharacter>(OtherActor))
	{
		player->TakeDamage(m_damage);
	}
}

void ADI_MeleeEnemy::Attack_Implementation()
{
	if (m_animMontage && m_canAttack)
	{
		m_canAttack = false;
		FTimerHandle timerHandle_AttackDelay;
		FTimerDelegate delegate;
		delegate.BindUFunction(this, "AttackDelay");

		GetWorld()->GetTimerManager().SetTimer(timerHandle_AttackDelay, delegate, m_attackAnimDelay, false);
		PlayAnimMontage(m_animMontage);
	}
	

	return;
}

void ADI_MeleeEnemy::AttackDelay()
{
	Super::AttackDelay();
	m_rightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ADI_MeleeEnemy::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	m_rightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADI_MeleeEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}