// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EPGameInstance.generated.h"

UCLASS()
class EARTH_PROJECT_API UEPGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    void QuitGame(APlayerController* SpecificPlayer);

protected:
    virtual void OnStart() override;
};
