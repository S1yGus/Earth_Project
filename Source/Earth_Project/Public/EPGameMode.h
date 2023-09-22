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
    FOnTimeChangedSignature OnTimeChanged;
    FOnSpeedChangedSignature OnSpeedChanged;

    AEPGameMode();

    FTimespan GetCurrentTimespan() const { return FTimespan::FromSeconds(Time); }
    float GetCurrentDay() const;
    float GetCurrentHour() const;

    float GetCurrentSpeedNormalized() const;
    void SetCurrentSpeedNormalized(float NormalizedSpeed);

    virtual void SetGameState(EGameState NewGameState);
    virtual void StartPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", Meta = (ClampMin = "0.0"))
    float Speed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", Meta = (ClampMin = "0.0"))
    float MaxSpeed = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", Meta = (ClampMin = "1", ClampMax = "365"))
    int32 Day = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", Meta = (ClampMin = "0", ClampMax = "23"))
    int32 Hour = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", Meta = (ClampMin = "0", ClampMax = "59"))
    int32 Minute = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", Meta = (ClampMin = "0", ClampMax = "59"))
    int32 Second = 0;

private:
    EGameState CurrentGameState = EGameState::WaitingToStart;

    FTimerHandle TimeTimerHandle;
    double Time = 0.0;

    void OnTimeTick();
};
