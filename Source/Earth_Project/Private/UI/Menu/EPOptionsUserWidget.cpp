// Earth_Project, All rights reserved.

#include "UI/Menu/EPOptionsUserWidget.h"
#include "UI/Menu/EPButtonUserWidget.h"
#include "Settings/EPGameUserSettings.h"
#include "UI/Menu/EPComboBoxSettingUserWidget.h"
#include "UI/Menu/EPSliderSettingUserWidget.h"
#include "EPGameMode.h"
#include "Settings/EPSetting.h"
#include "Settings/EPIntSetting.h"
#include "Settings/EPFloatSetting.h"
#include "Interfaces/EPSettingWidgetInterface.h"
#include "EPPlayerController.h"

void UEPOptionsUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(VideoSettingsVerticalBox);
    check(SoundSettingsVerticalBox);
    check(BackButton);

    if (auto* GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->OnResolutionChanged.AddUObject(this, &ThisClass::OnResolutionChanged);

        InitSettingsWidgets(GameUserSettings->GetVideoSettings(), VideoSettingsVerticalBox);
        InitSettingsWidgets(GameUserSettings->GetSoundSettings(), SoundSettingsVerticalBox);
    }

    if (auto* GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }

    if (auto* PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }

    BackButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedBackButton);
}

void UEPOptionsUserWidget::InitSettingsWidgets(const TArray<UEPSetting*>& SettingsArray, UVerticalBox* Container)
{
    Container->ClearChildren();

    for (auto* Setting : SettingsArray)
    {
        if (auto* IntSetting = Cast<UEPIntSetting>(Setting))
        {
            CreateAndAddSettingsWidget<UEPComboBoxSettingUserWidget>(ComboBoxSettingWidgetClass, IntSetting, Container);
        }
        else if (auto* FloatSetting = Cast<UEPFloatSetting>(Setting))
        {
            CreateAndAddSettingsWidget<UEPSliderSettingUserWidget>(SliderSettingWidgetClass, FloatSetting, Container);
        }
    }
}

void UEPOptionsUserWidget::UpdateWidgetsInContainer(const UVerticalBox* Container)
{
    for (const auto& Widget : Container->GetAllChildren())
    {
        if (auto* SettingWidget = Cast<IEPSettingWidgetInterface>(Widget))
        {
            SettingWidget->Update();
        }
    }
}

void UEPOptionsUserWidget::UpdateOptions()
{
    UpdateWidgetsInContainer(VideoSettingsVerticalBox);
    UpdateWidgetsInContainer(SoundSettingsVerticalBox);
}

void UEPOptionsUserWidget::ChangeGameState(EGameState NewGameState)
{
    GameStateToSet = NewGameState;
    ShowFadeoutAnimation();
}

void UEPOptionsUserWidget::OnGameStateChanged(EGameState NewGameState)
{
    if (NewGameState != EGameState::Options)
        return;

    GameStateToSet = EGameState::Options;
    UpdateOptions();
}

void UEPOptionsUserWidget::OnPressedEsc()
{
    if (!IsVisible() || IsAnyAnimationPlaying())
        return;

    OnClickedBackButton();
}

void UEPOptionsUserWidget::OnResolutionChanged()
{
    ChangeGameState(EGameState::OptionsWarning);
}

void UEPOptionsUserWidget::OnClickedBackButton()
{
    if (auto* GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->SaveSettings();
    }

    ChangeGameState(EGameState::Menu);
}

void UEPOptionsUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == FadeoutAnimation)
    {
        SetGameState(GameStateToSet);
    }
}
