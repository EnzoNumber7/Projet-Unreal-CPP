// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WDG_DIHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Weapon/TP_DIWeaponComponent.h"
#include "Weapon/DIWeaponData.h"
#include "DiabloIsac/DiabloIsacCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"
#include "EnhancedInputComponent.h"
#include "Components/Border.h"
#include "Components/Button.h"


void UWDG_DIHUD::NativeConstruct()
{
    Super::NativeConstruct();
    Character = Cast<ADiabloIsacCharacter>(GetOwningPlayerPawn());
    if (!Character) return;
    // Vérifie si la ProgressBar est bien assignée


    if (!ProgressBar)return;   
    ProgressBar->SetPercent(Character->GetPlayerHealth() / Character->GetPlayerMaxHealth());
    

    MagazineSize->SetVisibility(ESlateVisibility::Hidden);
    AmmoReserve->SetVisibility(ESlateVisibility::Hidden);

    Character->OnHealthChanged.AddDynamic(this, &UWDG_DIHUD::UpdateProgress);
    Character->OnWeaponPickUp.AddDynamic(this, &UWDG_DIHUD::SetDataWeapon);
    Character->OnWeaponFire.AddDynamic(this, &UWDG_DIHUD::UpdateMagazineSize);
    Character->OnWeaponReload.AddDynamic(this, &UWDG_DIHUD::UpdateAmmoReserve);
    Character->OnPlayerEnd.AddDynamic(this, &UWDG_DIHUD::SetBorderActive);
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
    EnhancedInputComponent->BindAction(pauseAction, ETriggerEvent::Started, this, &UWDG_DIHUD::OpenPauseMenu);

    BorderLose->SetVisibility(ESlateVisibility::Hidden);
    BorderWin->SetVisibility(ESlateVisibility::Hidden);


    pauseCanva->SetVisibility(ESlateVisibility::Collapsed);

    quitPauseButton->OnClicked.AddDynamic(this, &UWDG_DIHUD::OnClickQuitSettingButton);

    sfxSlider->OnValueChanged.AddDynamic(this, &UWDG_DIHUD::OnSFXSliderChange);
    musicSlider->OnValueChanged.AddDynamic(this, &UWDG_DIHUD::OnMusicSliderChange);


}

void UWDG_DIHUD::UpdateProgress(float newValue)
{
    ProgressBar->SetPercent(newValue);
}

void UWDG_DIHUD::SetDataWeapon(UDIWeaponData* WeaponData) {

    weaponData = Character->GetPlayerWeapon()->WeaponData;

    MagazineSize->SetVisibility(ESlateVisibility::Visible);
    AmmoReserve->SetVisibility(ESlateVisibility::Visible);

    if (!MagazineSize)return;
    MagazineSize->SetText(FText::FromString(FString::FromInt(weaponData->MagazineCapacity)));

    if (!AmmoReserve)return;
    AmmoReserve->SetText(FText::FromString(FString::FromInt(weaponData->AmmoReserve)));
}

void UWDG_DIHUD::UpdateMagazineSize(int ammo) {

    MagazineSize->SetText(FText::FromString(FString::FromInt(ammo)));
}

void UWDG_DIHUD::UpdateAmmoReserve(int magazineSize, int ammo)
{

    MagazineSize->SetText(FText::FromString(FString::FromInt(magazineSize)));

    AmmoReserve->SetText(FText::FromString(FString::FromInt(ammo)));

}

void UWDG_DIHUD::OnSFXSliderChange(float value)
{
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SFXSoundClass, value, 1.0f, 0.0f);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

void UWDG_DIHUD::OnMusicSliderChange(float value)
{
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, MusicSoundClass, value, 1.0f, 0.0f);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

void UWDG_DIHUD::OnClickQuitSettingButton()
{
    pauseCanva->SetVisibility(ESlateVisibility::Collapsed);
    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UWDG_DIHUD::OpenPauseMenu()
{
    pauseCanva->SetVisibility(ESlateVisibility::Visible);
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UWDG_DIHUD::SetBorderActive(bool value)
{
    if (value) {
        BorderWin->SetVisibility(ESlateVisibility::Visible);
    }
    else {

        BorderLose->SetVisibility(ESlateVisibility::Visible);
    }
}

