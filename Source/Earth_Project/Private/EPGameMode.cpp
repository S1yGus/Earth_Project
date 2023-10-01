// Earth_Project, All rights reserved.

#include "EPGameMode.h"
#include "EPPlayerController.h"
#include "UI/EPHUD.h"
#include "Pawns/EPEarth.h"
#include "TimeConstance.h"

using namespace TimeConstance;

constexpr static float TimeChangeTimerRate{0.016f};

AEPGameMode::AEPGameMode()
{
    PlayerControllerClass = AEPPlayerController::StaticClass();
    HUDClass = AEPHUD::StaticClass();
    DefaultPawnClass = AEPEarth::StaticClass();
}

float AEPGameMode::GetCurrentDay() const
{
    return FMath::Fmod((Seconds / SecondsInDay), DaysInYear) + 1.0f;    // The countdown starts from the first day.
}

float AEPGameMode::GetCurrentHour() const
{
    return FMath::Fmod(Seconds, SecondsInDay) / SecondsInHour;
}

float AEPGameMode::GetCurrentSpeedNormalized() const
{
    return Speed / MaxSpeed;
}

void AEPGameMode::SetCurrentSpeedNormalized(float NormalizedSpeed)
{
    if (NormalizedSpeed < 0.0f || NormalizedSpeed > MaxSpeed)
        return;

    Speed = NormalizedSpeed * MaxSpeed;
    OnSpeedChanged.Broadcast(Speed);
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

    Seconds = (DaysInYear - Equinox + Day) * SecondsInDay + Hour * SecondsInHour + Minute * SecondsInMinute + Second;
    GetWorldTimerManager().SetTimer(TimeChangeTimerHandle, this, &ThisClass::OnTimeChange, TimeChangeTimerRate, true);
}

void AEPGameMode::OnTimeChange()
{
    Seconds += Speed * TimeChangeTimerRate;
    OnTimeChanged.Broadcast(Seconds);
}
