// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EPCoreTypes.h"
#include "EPGameMode.generated.h"

UCLASS()
class EARTH_PROJECT_API AEPGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    FOnGameStateChangedSignature OnGameStateChanged;

    AEPGameMode();

    virtual void SetGameState(EGameState NewGameState);
    virtual void StartPlay() override;

private:
    EGameState CurrentGameState = EGameState::WaitingToStart;
};
