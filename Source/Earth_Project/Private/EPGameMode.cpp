// Earth_Project, All rights reserved.

#include "EPGameMode.h"
#include "EPPlayerController.h"
#include "UI/EPHUD.h"

AEPGameMode::AEPGameMode()
{
    PlayerControllerClass = AEPPlayerController::StaticClass();
    HUDClass = AEPHUD::StaticClass();
}

void AEPGameMode::SetGameState(EGameState NewGameState)
{
    if (CurrentGameState == NewGameState)
        return;

    CurrentGameState = NewGameState;
    OnGameStateChanged.Broadcast(NewGameState);
}

void AEPGameMode::StartPlay()
{
    Super::StartPlay();

    SetGameState(EGameState::Menu);
}
