// Earth_Project, All rights reserved.

#include "UI/Menu/EPOptionsWarningUserWidget.h"
#include "UI/Menu/EPButtonUserWidget.h"
#include "EPGameMode.h"
#include "Settings/EPGameUserSettings.h"
#include "EPPlayerController.h"

FText UEPOptionsWarningUserWidget::GetCountdownTime() const
{
    return FText::AsNumber(static_cast<int32>(CountdownTime));
}

void UEPOptionsWarningUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Setup();
}

void UEPOptionsWarningUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    CountdownTime -= InDeltaTime;
    if (CountdownTime <= 0.0f && !IsAnimationPlaying(FadeoutAnimation))
    {
        OnCancelSettings();
    }
}

void UEPOptionsWarningUserWidget::Setup()
{
    check(SaveButton);
    check(CancelButton);

    SaveButton->OnClickedButton.AddUObject(this, &ThisClass::OnSaveSettings);
    CancelButton->OnClickedButton.AddUObject(this, &ThisClass::OnCancelSettings);

    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }

    if (const auto PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEnt.AddUObject(this, &ThisClass::OnPressedEnter);
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }
}

void UEPOptionsWarningUserWidget::ResetWidget()
{
    CountdownTime = CancelSettingsTime;
}

void UEPOptionsWarningUserWidget::OnGameStateChanged(EGameState NewGameState)
{
    if (NewGameState != EGameState::OptionsWarning)
        return;

    ResetWidget();
}

void UEPOptionsWarningUserWidget::OnPressedEnter()
{
    if (!IsVisible() || IsAnyAnimationPlaying())
        return;

    OnSaveSettings();
}

void UEPOptionsWarningUserWidget::OnPressedEsc()
{
    if (!IsVisible() || IsAnyAnimationPlaying())
        return;

    OnCancelSettings();
}

void UEPOptionsWarningUserWidget::OnSaveSettings()
{
    const auto GameUserSettings = UEPGameUserSettings::Get();
    if (!GameUserSettings)
        return;

    GameUserSettings->ConfirmVideoMode();

    ShowFadeoutAnimation();
}

void UEPOptionsWarningUserWidget::OnCancelSettings()
{
    const auto GameUserSettings = UEPGameUserSettings::Get();
    if (!GameUserSettings)
        return;

    GameUserSettings->SetLastConfirmedResolutionSettings();

    ShowFadeoutAnimation();
}

void UEPOptionsWarningUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation != FadeoutAnimation)
        return;

    SetGameState(EGameState::Options);
}
