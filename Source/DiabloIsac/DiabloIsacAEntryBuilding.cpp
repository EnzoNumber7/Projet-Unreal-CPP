// Fill out your copyright notice in the Description page of Project Settings.


#include "DiabloIsacAEntryBuilding.h"
#include "Camera/CameraComponent.h"
#include "DiabloIsacCharacter.h"

// Sets default values
ADiabloIsacAEntryBuilding::ADiabloIsacAEntryBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->SetCollisionProfileName("OverlapAll", true);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Overlap);

	isInBuilding = false;
	isRotate = false;
	currentTime = 0;
}

// Called when the game starts or when spawned
void ADiabloIsacAEntryBuilding::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADiabloIsacAEntryBuilding::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADiabloIsacAEntryBuilding::OnOverlapExit);
}

// Called every frame
void ADiabloIsacAEntryBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isRotate) {
		currentTime += DeltaTime;
		float alpha = FMath::Clamp(currentTime, 0, 1);
		TopDownCamera->SetRelativeRotation(FMath::Lerp(currentRotation, afterRotation, alpha));
		if (alpha == 1) {
			isRotate = false;
			currentTime = 0;
			alpha = 0;
		}
	}

}

void ADiabloIsacAEntryBuilding::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!OtherActor)return;

	if (OtherActor->IsA(ADiabloIsacCharacter::StaticClass()))
	{
		ADiabloIsacCharacter* character = Cast<ADiabloIsacCharacter>(OtherActor);
		TopDownCamera = character->GetCameraBoom();
		currentRotation = TopDownCamera->GetRelativeRotation();
		if (character->GetIsInBuilding() == false) {
			afterRotation = FRotator(-90.f, 0.f, 0.f);
			character->SetIsInBuilding(true);
		}
		isRotate = true;
		currentTime = 0;
	}

	
}

void ADiabloIsacAEntryBuilding::OnOverlapExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (!OtherActor)return;

	if (OtherActor->IsA(ADiabloIsacCharacter::StaticClass()))
	{
		ADiabloIsacCharacter* character = Cast<ADiabloIsacCharacter>(OtherActor);
		TopDownCamera = character->GetCameraBoom();
		currentRotation = TopDownCamera->GetRelativeRotation();
		if (character->GetIsInBuilding() == true) {
			afterRotation = FRotator(-50.f, 0.f, 0.f);
			character->SetIsInBuilding(false);
		}
		isRotate = true;
		currentTime = 0;
	}
}

