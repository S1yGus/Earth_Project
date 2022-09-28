// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EPCoreTypes.h"
#include "EPSettingsSave.generated.h"

UCLASS()
class EARTH_PROJECT_API UEPSettingsSave : public USaveGame
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    FVideoSettings VideoSettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
    FSoundSettings SoundSettings;

    friend class UEPGameUserSettings;
};
