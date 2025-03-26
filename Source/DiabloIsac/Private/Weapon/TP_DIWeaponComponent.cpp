// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/TP_DIWeaponComponent.h"
#include "DiabloIsac/DiabloIsacCharacter.h"
#include "GameFramework/PlayerController.h"
#include "DiabloIsac/Public/Character/Animation/DIAnimator.h"
#include "Weapon/DIWeaponData.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon/DI_Projectile.h"

UTP_DIWeaponComponent::UTP_DIWeaponComponent()
{
}

void UTP_DIWeaponComponent::BeginPlay() {
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

}


bool UTP_DIWeaponComponent::AttachWeapon(ADiabloIsacCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character == nullptr || Character->GetHasWeapon()) return false;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));
	PlayerController = Cast<APlayerController>(Character->GetController());

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UTP_DIWeaponComponent::Fire);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &UTP_DIWeaponComponent::StopFire);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &UTP_DIWeaponComponent::Reload);

		}
	}

	Character->SetHasWeapon(true);
	Character->SetPlayerWeapon(this);

	CharacterAnimator = Cast<UDIAnimator>(Character->GetMesh()->GetAnimInstance());
	if (!CharacterAnimator) return false;
	CharacterAnimator->SetHasRifle(true);

	return true;
}

void UTP_DIWeaponComponent::SetWeaponData(UDIWeaponData* Data) {
    WeaponData = Data;
	magazineSize = WeaponData->MagazineCapacity;
	ammoReserve = WeaponData->AmmoReserve;
    SetSkeletalMesh(Data->Mesh);
}

void UTP_DIWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

}

void UTP_DIWeaponComponent::FireShot()
{
	
	
	CharacterAnimator->SetIsShooting(true);

	if (magazineSize <= 0) {
		Reload();
		return;
	}

	Character->GetCharacterMovement()->bOrientRotationToMovement = false;

	if (bIsReloading) return;

	FVector2D MousePosition;
	FVector MouseWorldPosition;
	FVector MouseWorldDirection;

	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	PlayerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, MouseWorldPosition, MouseWorldDirection);

	FVector Start = GetSocketLocation("AmmoSocket");
	float GroundZ = Start.Z;

	float T = (GroundZ - MouseWorldPosition.Z) / MouseWorldDirection.Z;
	FVector ProjectedMousePosition = MouseWorldPosition + (T * MouseWorldDirection);
	ProjectedMousePosition.Z = GroundZ;

	FVector Direction = (ProjectedMousePosition - Start).GetSafeNormal();

	FRotator NewRotation = FRotator(0.0f, Direction.Rotation().Yaw, 0.0f);

	Character->SetActorRotation(NewRotation);

	

	ADI_Projectile* currentProjectile = GetWorld()->SpawnActor<ADI_Projectile>(m_projectileActor, Start, Character->GetActorRotation());
	currentProjectile->SetDamage(WeaponData->DamageAmount);
	currentProjectile->SetOwnerId(0, Character);
	currentProjectile->SetLifeSpan(5);



	magazineSize--;
	Character->Fire();
}

void UTP_DIWeaponComponent::StopFire()
{
	bIsFiring = false;
	CharacterAnimator->SetIsShooting(false);
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
}

void UTP_DIWeaponComponent::Fire() {


	if (magazineSize <= 0)return;
	if (bIsFiring) return;

	bIsFiring = true;
	FireShot();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &UTP_DIWeaponComponent::FireShot, WeaponData->FireRate, true);

	if (!PlayerController || !Character) return;

	
}

void UTP_DIWeaponComponent::Reload() {
	
	CharacterAnimator->SetIsShooting(false);
	bIsReloading = true;

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &UTP_DIWeaponComponent::FinishReload, WeaponData->ReloadTime, false);
}

void UTP_DIWeaponComponent::FinishReload() {
	
	int needAmmo = WeaponData->MagazineCapacity - magazineSize;
	int ammoToReload = FMath::Min(needAmmo, ammoReserve);


	magazineSize += ammoToReload;
	ammoReserve -= ammoToReload;
	bIsReloading = false;
	Character->Reload();

}