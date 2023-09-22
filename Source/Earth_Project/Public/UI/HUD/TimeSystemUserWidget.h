// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeSystemUserWidget.generated.h"

class UTextBlock;
class USlider;

UCLASS()
class EARTH_PROJECT_API UTimeSystemUserWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(Meta = (BindWidget))
    UTextBlock* SpeedText;

    UPROPERTY(Meta = (BindWidget))
    USlider* SpeedSlider;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Text")
    int32 MinSpeedTextLength = 3;

    virtual void NativeOnInitialized() override;

private:
    void UpdateSpeedText(float NormalizedNewSpeed);

    UFUNCTION()
    void OnValueChanged(float Value);
    UFUNCTION()
    void OnMouseCaptureEnd();
};
