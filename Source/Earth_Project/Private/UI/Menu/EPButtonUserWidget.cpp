// Earth_Project, All rights reserved.

#include "UI/Menu/EPButtonUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UEPButtonUserWidget::SetText(const FText& NewText)
{
    ButtonText = NewText;
    ButtonTextBlock->SetText(ButtonText);
}

void UEPButtonUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Setup();
}

void UEPButtonUserWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    ButtonTextBlock->SetText(ButtonText);
}

void UEPButtonUserWidget::Setup()
{
    check(Button);
    check(ButtonTextBlock);

    Button->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
    Button->OnHovered.AddDynamic(this, &ThisClass::OnHovered);
    Button->OnUnhovered.AddDynamic(this, &ThisClass::OnUnhovered);
}

void UEPButtonUserWidget::OnClicked()
{
    Button->SetIsEnabled(false);
    PlayAnimation(OnClickedAnimation);
}

void UEPButtonUserWidget::OnHovered()
{
    PlayAnimationForward(OnHoveredAnimation);
}

void UEPButtonUserWidget::OnUnhovered()
{
    PlayAnimationReverse(OnHoveredAnimation);
}

void UEPButtonUserWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == OnClickedAnimation)
    {
        OnClickedButton.Broadcast();
        Button->SetIsEnabled(true);
    }
}
