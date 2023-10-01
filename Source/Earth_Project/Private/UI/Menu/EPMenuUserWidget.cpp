// Earth_Project, All rights reserved.

#include "UI/Menu/EPMenuUserWidget.h"
#include "UI/Menu/EPButtonUserWidget.h"
#include "EPGameMode.h"
#include "EPGameInstance.h"
#include "EPPlayerController.h"

void UEPMenuUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(StartButton);
    check(OptionsButton);
    check(QuitButton);

    StartButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedStartButton);
    OptionsButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedOptionsButton);
    QuitButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedQuitButton);

    if (auto* GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }

    if (auto* PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }
}

void UEPMenuUserWidget::ChangeGameStateWithAnimation(EGameState NewGameState)
{
    GameStateToSet = NewGameState;
    ShowFadeoutAnimation();
}

void UEPMenuUserWidget::OnGameStateChanged(EGameState NewGameState)
{
    if (NewGameState != EGameState::Menu)
        return;

    GameStateToSet = EGameState::Menu;
}

void UEPMenuUserWidget::OnPressedEsc()
{
    if (!IsVisible() || IsAnyAnimationPlaying())
        return;

    OnClickedStartButton();
}

void UEPMenuUserWidget::OnClickedStartButton()
{
    ChangeGameStateWithAnimation(EGameState::InProgramm);
}

void UEPMenuUserWidget::OnClickedOptionsButton()
{
    ChangeGameStateWithAnimation(EGameState::Options);
}

void UEPMenuUserWidget::OnClickedQuitButton()
{
    if (auto* GameInstnce = GetGameInstance<UEPGameInstance>())
    {
        GameInstnce->QuitGame(GetOwningPlayer());
    }
}

void UEPMenuUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == FadeoutAnimation)
    {
        SetGameState(GameStateToSet);
    }
}
