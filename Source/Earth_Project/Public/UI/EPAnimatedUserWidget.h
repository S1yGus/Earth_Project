// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EPCoreTypes.h"
#include "EPAnimatedUserWidget.generated.h"

class USoundCue;
class AEPGameMode;

UCLASS()
class EARTH_PROJECT_API UEPAnimatedUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ShowStartupAnimation();
    void ShowFadeoutAnimation();

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* StartupAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartupSound;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* FadeoutAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FadeoutSound;

    void SetGameState(EGameState NewGameState);
};
