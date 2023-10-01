// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/EPSettingWidgetInterface.h"
#include "EPSliderSettingUserWidget.generated.h"

class UEPFloatSetting;
class USlider;
class UTextBlock;

UCLASS()
class EARTH_PROJECT_API UEPSliderSettingUserWidget : public UUserWidget, public IEPSettingWidgetInterface
{
    GENERATED_BODY()

public:
    void Init(UEPFloatSetting* NewSetting);
    void UpdatePercentText();
    virtual void Update() override;

protected:
    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UTextBlock> SettingNameText;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<USlider> SettingSlider;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UTextBlock> PercentText;

    UPROPERTY()
    TObjectPtr<UEPFloatSetting> Setting;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnValueChanged(float Value);
    UFUNCTION()
    void OnMouseCaptureEnd();
};
