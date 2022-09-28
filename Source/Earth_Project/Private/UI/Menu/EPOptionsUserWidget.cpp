// Earth_Project, All rights reserved.

#include "UI/Menu/EPOptionsUserWidget.h"
#include "UI/Menu/EPButtonUserWidget.h"
#include "Components/VerticalBox.h"
#include "Settings/EPGameUserSettings.h"
#include "UI/Menu/EPComboBoxSettingUserWidget.h"
#include "UI/Menu/EPSliderSettingUserWidget.h"
#include "EPGameMode.h"
#include "UI/EPHUD.h"
#include "Settings/EPSetting.h"
#include "Settings/EPIntSetting.h"
#include "Settings/EPFloatSetting.h"
#include "Interfaces/EPSettingWidgetInterface.h"
#include "EPPlayerController.h"

#define UPDATE_SETTINGS_WIDGETS(ContainerWidget)                                \
    for (const auto& Widget : ContainerWidget->GetAllChildren())                \
    {                                                                           \
        if (const auto SettingWidget = Cast<IEPSettingWidgetInterface>(Widget)) \
        {                                                                       \
            SettingWidget->Update();                                            \
        }                                                                       \
    }

#define CREATE_AND_ADD_SETTING_WIDGET(T, WidgetClass, Setting, ToContainerWidget) \
    T* SettingWidget = CreateWidget<T>(GetWorld(), WidgetClass);                  \
    check(SettingWidget);                                                         \
    SettingWidget->Init(Setting);                                                 \
    ToContainerWidget->AddChild(SettingWidget);

void UEPOptionsUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Setup();
}

void UEPOptionsUserWidget::InitSettingsWidgets(const TArray<UEPSetting*>& SettingsArray, UVerticalBox* VerticalBox)
{
    VerticalBox->ClearChildren();

    for (const auto& Setting : SettingsArray)
    {
        if (const auto& IntSetting = Cast<UEPIntSetting>(Setting))
        {
            CREATE_AND_ADD_SETTING_WIDGET(UEPComboBoxSettingUserWidget, ComboBoxSettingWidgetClass, IntSetting, VerticalBox);
        }
        else if (const auto& FloatSetting = Cast<UEPFloatSetting>(Setting))
        {
            CREATE_AND_ADD_SETTING_WIDGET(UEPSliderSettingUserWidget, SliderSettingWidgetClass, FloatSetting, VerticalBox);
        }
    }
}

void UEPOptionsUserWidget::Setup()
{
    check(VideoSettingsVerticalBox);
    check(SoundSettingsVerticalBox);
    check(BackButton);

    if (const auto GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->OnResolutionChanged.AddUObject(this, &ThisClass::OnResolutionChanged);

        InitSettingsWidgets(GameUserSettings->GetVideoSettings(), VideoSettingsVerticalBox);
        InitSettingsWidgets(GameUserSettings->GetSoundSettings(), SoundSettingsVerticalBox);
    }

    BackButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedBackButton);

    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }

    if (const auto PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }
}

void UEPOptionsUserWidget::ResetWidget()
{
    GameStateToSet = EGameState::Options;
    UpdateOptions();
}

void UEPOptionsUserWidget::UpdateOptions()
{
    UPDATE_SETTINGS_WIDGETS(VideoSettingsVerticalBox);
    UPDATE_SETTINGS_WIDGETS(SoundSettingsVerticalBox);
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

    ResetWidget();
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
    if (const auto GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->SaveSettings();
    }

    ChangeGameState(EGameState::Menu);
}

void UEPOptionsUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation != FadeoutAnimation)
        return;

    SetGameState(GameStateToSet);
}
