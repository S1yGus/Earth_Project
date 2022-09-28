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
    UEPButtonUserWidget* StartButton;

    UPROPERTY(Meta = (BindWidget))
    UEPButtonUserWidget* OptionsButton;

    UPROPERTY(Meta = (BindWidget))
    UEPButtonUserWidget* QuitButton;

    virtual void NativeOnInitialized() override;

private:
    EGameState GameStateToSet = EGameState::Menu;

    void Setup();
    void ResetWidget();

    void ChangeGameState(EGameState NewGameState);

    void OnGameStateChanged(EGameState NewGameState);
    void OnPressedEsc();
    void OnClickedStartButton();
    void OnClickedOptionsButton();
    void OnClickedQuitButton();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
