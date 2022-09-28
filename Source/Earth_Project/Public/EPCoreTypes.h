// Earth_Project, All rights reserved.

#pragma once

#include "EPCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
    WaitingToStart,
    Menu,
    Options,
    OptionsWarning,
    InProgramm,
    Max
};

USTRUCT(BlueprintType)
struct FAspectRatioData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    float AspectRatio = 1.7777777f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    float FOV = 90.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    FText DisplayName{FText::FromString("16:9")};
};

USTRUCT(BlueprintType)
struct FVideoSettings
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    FAspectRatioData AspectRatioData;
};

USTRUCT(BlueprintType)
struct FSoundSettings
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", Meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float MasterVolume = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", Meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float UIVolume = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", Meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float FXVolume = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", Meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float MusicVolume = 0.5f;
};

USTRUCT(BlueprintType)
struct FCultureData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Culture")
    FString Culture;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Culture")
    FText CultureName;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState);
DECLARE_MULTICAST_DELEGATE(FOnClickedButtonSignature);
DECLARE_MULTICAST_DELEGATE(FOnPressedEscSignature);
DECLARE_MULTICAST_DELEGATE(FOnPressedEnterSignature);
DECLARE_MULTICAST_DELEGATE(FOnResolutionChangedSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAspectRatioChangedSignature, const FAspectRatioData&);
