// Earth_Project, All rights reserved.

#include "UI/Menu/EPOptionsWarningUserWidget.h"
#include "UI/Menu/EPButtonUserWidget.h"
#include "EPGameMode.h"
#include "Settings/EPGameUserSettings.h"
#include "EPPlayerController.h"

FText UEPOptionsWarningUserWidget::GetCountdownTime() const
{
    return FText::AsNumber(FMath::RoundToInt(CountdownTime));
}

void UEPOptionsWarningUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(SaveButton);
    check(CancelButton);

    SaveButton->OnClickedButton.AddUObject(this, &ThisClass::OnSaveSettings);
    CancelButton->OnClickedButton.AddUObject(this, &ThisClass::OnCancelSettings);

    if (GetWorld())
    {
        if (auto* GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
        {
            GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
        }
    }

    if (auto* PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEnt.AddUObject(this, &ThisClass::OnPressedEnter);
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }
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

void UEPOptionsWarningUserWidget::OnGameStateChanged(EGameState NewGameState)
{
    if (NewGameState == EGameState::OptionsWarning)
    {
        CountdownTime = CancelSettingsTime;
    }
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
    if (auto* GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->ConfirmVideoMode();
        ShowFadeoutAnimation();
    }
}

void UEPOptionsWarningUserWidget::OnCancelSettings()
{
    if (auto* GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->SetLastConfirmedResolutionSettings();
        ShowFadeoutAnimation();
    }
}

void UEPOptionsWarningUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == FadeoutAnimation)
    {
        SetGameState(EGameState::Options);
    }
}
