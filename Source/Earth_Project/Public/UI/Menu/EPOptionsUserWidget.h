// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/EPAnimatedUserWidget.h"
#include "EPCoreTypes.h"
#include "Components/VerticalBox.h"
#include "EPOptionsUserWidget.generated.h"

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
    TObjectPtr<UVerticalBox> VideoSettingsVerticalBox;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UVerticalBox> SoundSettingsVerticalBox;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UEPButtonUserWidget> BackButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UEPComboBoxSettingUserWidget> ComboBoxSettingWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UEPSliderSettingUserWidget> SliderSettingWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    EGameState GameStateToSet{EGameState::Options};

    void InitSettingsWidgets(const TArray<UEPSetting*>& SettingsArray, UVerticalBox* Container);
    void UpdateWidgetsInContainer(const UVerticalBox* Container);
    void UpdateOptions();

    void ChangeGameState(EGameState NewGameState);

    void OnGameStateChanged(EGameState NewGameState);
    void OnPressedEsc();
    void OnResolutionChanged();
    void OnClickedBackButton();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

    template <class WidgetClass, class SettingClass>
    void CreateAndAddSettingsWidget(TSubclassOf<UUserWidget> SettingWidgetClass, SettingClass* Setting, UVerticalBox* Container)
    {
        WidgetClass* SettingWidget = CreateWidget<WidgetClass>(GetWorld(), SettingWidgetClass);
        check(SettingWidget);
        SettingWidget->Init(Setting);
        Container->AddChild(SettingWidget);
    }
};
