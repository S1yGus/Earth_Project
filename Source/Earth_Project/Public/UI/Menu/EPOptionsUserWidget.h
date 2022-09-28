// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/EPAnimatedUserWidget.h"
#include "EPCoreTypes.h"
#include "EPOptionsUserWidget.generated.h"

class UVerticalBox;
class UEPButtonUserWidget;
class UEPComboBoxSettingUserWidget;
class UEPSliderSettingUserWidget;
class UEPSetting;

UCLASS()
class EARTH_PROJECT_API UEPOptionsUserWidget : public UEPAnimatedUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(Meta = (BindWidget))
    UVerticalBox* VideoSettingsVerticalBox;

    UPROPERTY(Meta = (BindWidget))
    UVerticalBox* SoundSettingsVerticalBox;

    UPROPERTY(Meta = (BindWidget))
    UEPButtonUserWidget* BackButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UEPComboBoxSettingUserWidget> ComboBoxSettingWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UEPSliderSettingUserWidget> SliderSettingWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    EGameState GameStateToSet = EGameState::Options;

    void InitSettingsWidgets(const TArray<UEPSetting*>& SettingsArray, UVerticalBox* VerticalBox);

    void Setup();

    void ResetWidget();
    void UpdateOptions();

    void ChangeGameState(EGameState NewGameState);

    void OnGameStateChanged(EGameState NewGameState);
    void OnPressedEsc();
    void OnResolutionChanged();
    void OnClickedBackButton();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
