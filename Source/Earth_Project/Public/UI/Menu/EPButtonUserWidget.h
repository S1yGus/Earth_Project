// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EPCoreTypes.h"
#include "EPButtonUserWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class EARTH_PROJECT_API UEPButtonUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    FOnClickedButtonSignature OnClickedButton;

    void SetText(const FText& NewText);

protected:
    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UButton> Button;

    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<UTextBlock> ButtonTextBlock;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> OnClickedAnimation;

    UPROPERTY(Meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> OnHoveredAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FText ButtonText;

    virtual void NativeOnInitialized() override;
    virtual void NativePreConstruct() override;

private:
    UFUNCTION()
    void OnClicked();
    UFUNCTION()
    void OnHovered();
    UFUNCTION()
    void OnUnhovered();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
