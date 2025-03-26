// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiabloIsacCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Manager/DIGameInstance.h"
#include "Weapon/TP_DIWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/World.h"

ADiabloIsacCharacter::ADiabloIsacCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	m_weaponComponent = nullptr;

	SetupStimulusSource();

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Game/Project/SFX/gunSFX.gunSFX"));
	if (SoundAsset.Succeeded())
	{
		SoundToPlay = SoundAsset.Object;
	}
}

void ADiabloIsacCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ADiabloIsacCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCurrentHealth = PlayerMaxHealth;
	OnHealthChanged.Broadcast(PlayerCurrentHealth / PlayerMaxHealth);

}

void ADiabloIsacCharacter::SetupStimulusSource()
{
	m_stimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));

	if (!m_stimulusSource)
		return;

	m_stimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	m_stimulusSource->RegisterWithPerceptionSystem();
}

void ADiabloIsacCharacter::TakeDamage(float DamageAmount) {

	PlayerCurrentHealth -= DamageAmount;
	
	OnHealthChanged.Broadcast(PlayerCurrentHealth / PlayerMaxHealth);
	if (PlayerCurrentHealth <= 0)
	{
		OnPlayerEnd.Broadcast(false);
		this->Destroy();
	}
}

void ADiabloIsacCharacter::ReceiveHealing(float HealAmount)
{
	PlayerCurrentHealth += HealAmount;

	if (PlayerCurrentHealth > PlayerMaxHealth) PlayerCurrentHealth = PlayerMaxHealth;
	OnHealthChanged.Broadcast(PlayerCurrentHealth / PlayerMaxHealth);
}

void ADiabloIsacCharacter::SetCharacterSpeed(float speedFactor,float duration) {

	float WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * speedFactor;
	
	FTimerHandle timerHandle;
	FTimerDelegate delegate;
	delegate.BindUFunction(this, "ResetWalkSpeed", WalkSpeed);
	
	GetWorld()->GetTimerManager().SetTimer(timerHandle, delegate, duration, false);

}

void ADiabloIsacCharacter::RefillAmmoReserve()
{
	m_weaponComponent->SetAmmoReserve(m_weaponComponent->WeaponData->AmmoReserve);
	OnWeaponReload.Broadcast(m_weaponComponent->GetMagazineSize(), m_weaponComponent->GetAmmoReserve());
}

void ADiabloIsacCharacter::ResetWalkSpeed(float walkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

}


void ADiabloIsacCharacter::SetPlayerWeapon(UTP_DIWeaponComponent* weapon) {

	m_weaponComponent = weapon;
	OnWeaponPickUp.Broadcast(weapon->WeaponData);
}

void ADiabloIsacCharacter::Fire() {

	OnWeaponFire.Broadcast(m_weaponComponent->GetMagazineSize());

	if (SoundToPlay) {
		UGameplayStatics::UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
	}
}

void ADiabloIsacCharacter::Reload() {

	OnWeaponReload.Broadcast(m_weaponComponent->GetMagazineSize(),m_weaponComponent->GetAmmoReserve());
}