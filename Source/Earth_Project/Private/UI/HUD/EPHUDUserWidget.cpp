// Earth_Project, All rights reserved.

#include "UI/HUD/EPHUDUserWidget.h"
#include "EPPlayerController.h"

void UEPHUDUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (auto* PC = GetOwningPlayer<AEPPlayerController>())
    {
        PC->OnPressedEsc.AddUObject(this, &ThisClass::OnPressedEsc);
    }
}

void UEPHUDUserWidget::OnPressedEsc()
{
    if (!IsVisible() || IsAnyAnimationPlaying())
        return;

    ShowFadeoutAnimation();
}

void UEPHUDUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == FadeoutAnimation)
    {
        SetGameState(EGameState::Menu);
    }
}
