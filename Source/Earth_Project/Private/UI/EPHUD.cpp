// Earth_Project, All rights reserved.

#include "UI/EPHUD.h"
#include "EPGameMode.h"
#include "UI/EPAnimatedUserWidget.h"

void AEPHUD::BeginPlay()
{
    Super::BeginPlay();

    check(MenuWidgetClass);
    check(OptionsWidgetClass);
    check(OptionsWarningWidgetClass);
    check(HUDWidgetClass);

    SetupWidgets();

    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }
}

void AEPHUD::SetupWidgets()
{
    GameWidgets.Add(EGameState::Menu, CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass));
    GameWidgets.Add(EGameState::Options, CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass));
    GameWidgets.Add(EGameState::OptionsWarning, CreateWidget<UUserWidget>(GetWorld(), OptionsWarningWidgetClass));
    GameWidgets.Add(EGameState::InProgramm, CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass));

    for (const auto& [GameState, GameWidget] : GameWidgets)
    {
        if (!GameWidget)
            continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AEPHUD::OnGameStateChanged(EGameState GameState)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (GameWidgets.Contains(GameState))
    {
        CurrentWidget = GameWidgets[GameState];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);

        if (const auto AnimatedWidget = Cast<UEPAnimatedUserWidget>(CurrentWidget))
        {
            AnimatedWidget->ShowStartupAnimation();
        }
    }
}
