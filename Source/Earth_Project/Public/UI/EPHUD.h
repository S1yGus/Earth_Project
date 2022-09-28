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

public:
    inline UUserWidget* GetCurretnWidget() { return CurrentWidget; }

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
    TMap<EGameState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget;

    virtual void BeginPlay() override;
    virtual void SetupWidgets();

private:
    void OnGameStateChanged(EGameState GameState);
};
