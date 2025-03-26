// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DI_GunEnemy.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/DI_Projectile.h"

ADI_GunEnemy::ADI_GunEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Project/SFX/gunSFX.gunSFX"));
	if (SoundAsset.Succeeded())
	{
		SoundToPlay = SoundAsset.Object;
	}
}

void ADI_GunEnemy::BeginPlay()
{
	Super::BeginPlay();

	UActorComponent* comp = GetComponentByClass(UStaticMeshComponent::StaticClass());
	if (comp->GetName() == TEXT("gun"))
		m_gunMesh = Cast<UStaticMeshComponent>(comp);


}

// Called every frame
void ADI_GunEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADI_GunEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADI_GunEnemy::Attack_Implementation()
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

void ADI_GunEnemy::AttackDelay()
{
	Super::AttackDelay();

	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (pawn == nullptr)
		return;
	FVector Player = pawn->GetActorLocation();

	FVector Start = m_gunMesh->GetSocketLocation("AmmoSocket");

	FVector Direction = (Player - Start).GetSafeNormal();

	FRotator NewRotation = FRotator(0.0f, Direction.Rotation().Yaw, 0.0f);

	SetActorRotation(NewRotation);

	ADI_Projectile* currentProjectile = GetWorld()->SpawnActor<ADI_Projectile>(m_projectileActor, Start, GetActorRotation());
	currentProjectile->SetDamage(m_damage);
	currentProjectile->SetOwnerId(1, this);

	if (SoundToPlay) {
		UGameplayStatics::UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
	}

}