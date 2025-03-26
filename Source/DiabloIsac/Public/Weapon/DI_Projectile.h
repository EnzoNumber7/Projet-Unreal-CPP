// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DI_Projectile.generated.h"

UCLASS()
class DIABLOISAC_API ADI_Projectile : public AActor
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	ADI_Projectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float damage);

	void SetOwnerId(int ownerId, AActor* ownerActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float m_damage;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* m_projectileMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* m_projectileComponent;


	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse,const FHitResult& Hit);
	// if id = 0 owner is player, if id = 1 owner is enemy
	int m_ownerId;
};
