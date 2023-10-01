// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EPCoreTypes.h"
#include "EPHUD.generated.h"

class UEPAnimatedUserWidget;

UCLASS()
class EARTH_PROJECT_API AEPHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> OptionsWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> OptionsWarningWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    UPROPERTY()
    TMap<EGameState, TObjectPtr<UUserWidget>> GameWidgets;

    virtual void BeginPlay() override;
    virtual void SetupWidgets();

private:
    UPROPERTY()
    TObjectPtr<UUserWidget> CurrentWidget;

    void OnGameStateChanged(EGameState GameState);
};
