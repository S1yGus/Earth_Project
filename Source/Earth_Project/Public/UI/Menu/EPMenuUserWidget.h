// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/EPAnimatedUserWidget.h"
#include "EPCoreTypes.h"
#include "EPMenuUserWidget.generated.h"

class UEPButtonUserWidget;

UCLASS()
class EARTH_PROJECT_API UEPMenuUserWidget : public UEPAnimatedUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UEPButtonUserWidget> StartButton;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UEPButtonUserWidget> OptionsButton;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UEPButtonUserWidget> QuitButton;

    virtual void NativeOnInitialized() override;

private:
    EGameState GameStateToSet{EGameState::Menu};

    FORCEINLINE void ChangeGameStateWithAnimation(EGameState NewGameState);

    void OnGameStateChanged(EGameState NewGameState);
    void OnPressedEsc();
    void OnClickedStartButton();
    void OnClickedOptionsButton();
    void OnClickedQuitButton();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
