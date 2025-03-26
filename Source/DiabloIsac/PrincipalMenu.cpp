// Fill out your copyright notice in the Description page of Project Settings.


#include "PrincipalMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/Slider.h"


void UPrincipalMenu::NativeConstruct()
{
	Super::NativeConstruct();

	settingsCanva->SetVisibility(ESlateVisibility::Collapsed);

	playButton->OnClicked.AddDynamic(this, &UPrincipalMenu::OnClickPlayButton);
	exitButton->OnClicked.AddDynamic(this, &UPrincipalMenu::OnClickExitButton);
	settingsButton->OnClicked.AddDynamic(this, &UPrincipalMenu::OnClickSettingButton);
	quitSettingsButton->OnClicked.AddDynamic(this, &UPrincipalMenu::OnClickQuitSettingButton);

	sfxSlider->OnValueChanged.AddDynamic(this, &UPrincipalMenu::OnSFXSliderChange);
	musicSlider->OnValueChanged.AddDynamic(this, &UPrincipalMenu::OnMusicSliderChange);
}

void UPrincipalMenu::OnSFXSliderChange(float value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SFXSoundClass, value, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

void UPrincipalMenu::OnMusicSliderChange(float value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, MusicSoundClass, value, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}


void UPrincipalMenu::OnClickPlayButton()
{
	UWorld* World = GetWorld();
	UGameplayStatics::OpenLevel(World, "Level");
}

void UPrincipalMenu::OnClickExitButton()
{
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UWorld* World = GetWorld();
	UKismetSystemLibrary::QuitGame(World, UGameplayStatics::GetPlayerController(World, 0), QuitPreference, true);
}

void UPrincipalMenu::OnClickSettingButton()
{
	settingsCanva->SetVisibility(ESlateVisibility::Visible);
}

void UPrincipalMenu::OnClickQuitSettingButton()
{
	settingsCanva->SetVisibility(ESlateVisibility::Collapsed);
}