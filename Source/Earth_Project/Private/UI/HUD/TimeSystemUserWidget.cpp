// Earth_Project, All rights reserved.

#include "UI/HUD/TimeSystemUserWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "EPGameMode.h"
#include "EPUtils.h"

void UTimeSystemUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(SpeedText);
    check(SpeedSlider);

    SpeedSlider->OnValueChanged.AddDynamic(this, &ThisClass::OnValueChanged);
    SpeedSlider->OnMouseCaptureEnd.AddDynamic(this, &ThisClass::OnMouseCaptureEnd);

    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        const auto NormalizedCurrentSpeed = GameMode->GetCurrentSpeedNormalized();
        SpeedSlider->SetValue(NormalizedCurrentSpeed);
        UpdateSpeedText(NormalizedCurrentSpeed);
    }
}

void UTimeSystemUserWidget::UpdateSpeedText(float NormalizedNewSpeed)
{
    SpeedText->SetText(EPUtils::FormatTextFromInt(static_cast<int32>(NormalizedNewSpeed * 100.0f), MinSpeedTextLength));
}

void UTimeSystemUserWidget::OnValueChanged(float Value)
{
    UpdateSpeedText(Value);
}

void UTimeSystemUserWidget::OnMouseCaptureEnd()
{
    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->SetCurrentSpeedNormalized(SpeedSlider->GetNormalizedValue());
    }
}
