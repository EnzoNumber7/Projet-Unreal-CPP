// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/DI_Projectile.h"
#include "AI/Enemy.h"
#include "DiabloIsac/DiabloIsacCharacter.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
ADI_Projectile::ADI_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	m_projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = m_projectileMesh;

	m_projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));

}

// Called when the game starts or when spawned
void ADI_Projectile::BeginPlay()
{
	Super::BeginPlay();
	m_projectileMesh->OnComponentHit.AddDynamic(this, &ADI_Projectile::OnCollisionEnter);
	m_ownerId = -1;

}

void ADI_Projectile::SetDamage(float damage)
{
	m_damage = damage;
}

void ADI_Projectile::SetOwnerId(int ownerId, AActor* ownerActor)
{
	m_ownerId = ownerId;

	m_projectileMesh->IgnoreActorWhenMoving(ownerActor, true);
}

// Called every frame
void ADI_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADI_Projectile::OnCollisionEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit)
{
	if (m_ownerId == -1)
		return;

	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	ADiabloIsacCharacter* character = Cast<ADiabloIsacCharacter>(OtherActor);
	if (enemy && m_ownerId == 0)
	{
		enemy->TakeDamage(m_damage);
		this->Destroy();
		return;
	}

	if (character && m_ownerId == 1)
	{
		character->TakeDamage(m_damage);
		this->Destroy();
		return;
	}

	if (ADI_Projectile* bullet = Cast<ADI_Projectile>(OtherActor))
		return;


	this->Destroy();

}

