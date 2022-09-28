// Earth_Project, All rights reserved.

#include "UI/Menu/EPSliderSettingUserWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Settings/EPFloatSetting.h"

void UEPSliderSettingUserWidget::Init(UEPFloatSetting* NewSetting)
{
    if (!NewSetting)
        return;

    Setting = NewSetting;
    SettingNameText->SetText(Setting->GetName());

    Update();
}

void UEPSliderSettingUserWidget::UpdatePercentText()
{
    const auto PercentStr = FString::Printf(TEXT("%.0f%%"), SettingSlider->GetNormalizedValue() * 100.0f);    // * 100.0f for 100%.
    PercentText->SetText(FText::FromString(PercentStr));
}

void UEPSliderSettingUserWidget::Update()
{
    if (!Setting)
        return;

    SettingSlider->SetValue(Setting->GetCurrentValue());

    UpdatePercentText();
}

void UEPSliderSettingUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(SettingNameText);
    check(SettingSlider);
    check(PercentText);

    SettingSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnValueChanged);
    SettingSlider->OnMouseCaptureEnd.AddDynamic(this, &ThisClass::OnMouseCaptureEnd);
}

void UEPSliderSettingUserWidget::OnValueChanged(float Value)
{
    UpdatePercentText();
}

void UEPSliderSettingUserWidget::OnMouseCaptureEnd()
{
    if (!Setting)
        return;

    Setting->SetValue(SettingSlider->GetNormalizedValue());
}
