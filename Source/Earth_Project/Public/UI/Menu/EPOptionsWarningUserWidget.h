// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/EPAnimatedUserWidget.h"
#include "EPCoreTypes.h"
#include "EPOptionsWarningUserWidget.generated.h"

class UEPButtonUserWidget;

UCLASS()
class EARTH_PROJECT_API UEPOptionsWarningUserWidget : public UEPAnimatedUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FText GetCountdownTime() const;

protected:
    UPROPERTY(Meta = (BindWidget))
    UEPButtonUserWidget* SaveButton;

    UPROPERTY(Meta = (BindWidget))
    UEPButtonUserWidget* CancelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float CancelSettingsTime = 10.0f;

    virtual void NativeOnInitialized() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    float CountdownTime = 0.0f;

    void Setup();
    void ResetWidget();

    void OnGameStateChanged(EGameState NewGameState);
    void OnPressedEnter();
    void OnPressedEsc();
    void OnSaveSettings();
    void OnCancelSettings();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
