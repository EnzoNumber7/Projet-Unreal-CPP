// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PrincipalMenu.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOISAC_API UPrincipalMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* playButton;

	UPROPERTY(meta = (BindWidget))
	UButton* exitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* settingsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* quitSettingsButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* settingsCanva;

	UPROPERTY(meta = (BindWidget))
	class USlider* sfxSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* musicSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundMix* SoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundClass* SFXSoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundClass* MusicSoundClass;

	UFUNCTION()
	void OnClickPlayButton();

	UFUNCTION()
	void OnClickExitButton();

	UFUNCTION()
	void OnClickSettingButton();

	UFUNCTION()
	void OnClickQuitSettingButton();

	UFUNCTION()
	void OnSFXSliderChange(float value);

	UFUNCTION()
	void OnMusicSliderChange(float value);
};
