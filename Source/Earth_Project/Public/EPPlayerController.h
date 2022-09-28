// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EPCoreTypes.h"
#include "EPPlayerController.generated.h"

UCLASS()
class EARTH_PROJECT_API AEPPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    FOnPressedEnterSignature OnPressedEnt;
    FOnPressedEscSignature OnPressedEsc;

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

private:
    void OnPressedEnter();
    void OnPressedEscape();
};
