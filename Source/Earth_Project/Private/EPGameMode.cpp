// Earth_Project, All rights reserved.

#include "EPGameMode.h"
#include "EPPlayerController.h"
#include "UI/EPHUD.h"
#include "Pawns/EPEarth.h"
#include "TimeConstance.h"

using namespace TimeConstance;

constexpr static float TimerRate = 0.016f;

AEPGameMode::AEPGameMode()
{
    PlayerControllerClass = AEPPlayerController::StaticClass();
    HUDClass = AEPHUD::StaticClass();
    DefaultPawnClass = AEPEarth::StaticClass();
}

float AEPGameMode::GetCurrentDay() const
{
    return FMath::Fmod((Time / SecondsInDay), DaysInYear) + 1.0f;    // The countdown starts from the first day.
}

float AEPGameMode::GetCurrentHour() const
{
    return FMath::Fmod(Time, SecondsInDay) / SecondsInHour;
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

    Time = (DaysInYear - Equinox + Day) * SecondsInDay + Hour * SecondsInHour + Minute * SecondsInMinute + Second;
    GetWorldTimerManager().SetTimer(TimeTimerHandle, this, &ThisClass::OnTimeTick, TimerRate, true);
}

void AEPGameMode::OnTimeTick()
{
    Time += Speed * TimerRate;
    OnTimeChanged.Broadcast(Time);
}
