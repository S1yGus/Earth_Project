// Earth_Project, All rights reserved.

#include "UI/Menu/EPMenuUserWidget.h"
#include "UI/Menu/EPButtonUserWidget.h"
#include "EPGameMode.h"
#include "EPGameInstance.h"
#include "EPPlayerController.h"

void UEPMenuUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Setup();
}

void UEPMenuUserWidget::Setup()
{
    check(StartButton);
    check(OptionsButton);
    check(QuitButton);

    StartButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedStartButton);
    OptionsButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedOptionsButton);
    QuitButton->OnClickedButton.AddUObject(this, &ThisClass::OnClickedQuitButton);

    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }

    if (const auto PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }
}

void UEPMenuUserWidget::ResetWidget()
{
    GameStateToSet = EGameState::Menu;
}

void UEPMenuUserWidget::ChangeGameState(EGameState NewGameState)
{
    GameStateToSet = NewGameState;
    ShowFadeoutAnimation();
}

void UEPMenuUserWidget::OnGameStateChanged(EGameState NewGameState)
{
    if (NewGameState != EGameState::Menu)
        return;

    ResetWidget();
}

void UEPMenuUserWidget::OnPressedEsc()
{
    if (!IsVisible() || IsAnyAnimationPlaying())
        return;

    OnClickedStartButton();
}

void UEPMenuUserWidget::OnClickedStartButton()
{
    ChangeGameState(EGameState::InProgramm);
}

void UEPMenuUserWidget::OnClickedOptionsButton()
{
    ChangeGameState(EGameState::Options);
}

void UEPMenuUserWidget::OnClickedQuitButton()
{
    const auto GameInstnce = GetGameInstance<UEPGameInstance>();
    if (!GameInstnce)
        return;

    GameInstnce->QuitGame(GetOwningPlayer());
}

void UEPMenuUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation != FadeoutAnimation)
        return;

    SetGameState(GameStateToSet);
}
