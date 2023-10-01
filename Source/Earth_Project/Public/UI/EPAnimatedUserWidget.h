// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EPCoreTypes.h"
#include "EPAnimatedUserWidget.generated.h"

class USoundCue;

UCLASS()
class EARTH_PROJECT_API UEPAnimatedUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void ShowStartupAnimation();
    void ShowFadeoutAnimation();

protected:
    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> StartupAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> StartupSound;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> FadeoutAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> FadeoutSound;

    void SetGameState(EGameState NewGameState);
};
