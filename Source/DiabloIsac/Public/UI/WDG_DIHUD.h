// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WDG_DIHUD.generated.h"

class UProgressBar;
class UTextBlock;
class UDIWeaponData;
class ADiabloIsacCharacter;

UCLASS()
class DIABLOISAC_API UWDG_DIHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct()override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateProgress(float newValue);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetDataWeapon(UDIWeaponData* WeaponData);

	UFUNCTION(BlueprintCallable, Category = "Magazine")
	void UpdateMagazineSize(int ammo);

	UFUNCTION(BlueprintCallable, Category = "Reserve")
	void UpdateAmmoReserve(int magazineSize, int ammo);

	UFUNCTION()
	void OnClickQuitSettingButton();

	UFUNCTION()
	void OnSFXSliderChange(float value);

	UFUNCTION()
	void OnMusicSliderChange(float value);

	UFUNCTION()
	void OpenPauseMenu();

	UFUNCTION()
	void SetBorderActive(bool value);

protected:

	UPROPERTY(meta = (BindWidget));
	UProgressBar* ProgressBar;

	UPROPERTY(meta = (BindWidget));
	UTextBlock* MagazineSize;

	UPROPERTY(meta = (BindWidget));
	UTextBlock* AmmoReserve;

	UDIWeaponData* weaponData;

	ADiabloIsacCharacter* Character;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputAction* pauseAction;

	UPROPERTY(meta = (BindWidget))
	class UButton* quitPauseButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* pauseCanva;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lose Screen")
	class UBorder* BorderLose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Win Screen")
	class UBorder* BorderWin;
};
