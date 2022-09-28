// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/EPAnimatedUserWidget.h"
#include "EPHUDUserWidget.generated.h"

UCLASS()
class EARTH_PROJECT_API UEPHUDUserWidget : public UEPAnimatedUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

private:
    void OnPressedEsc();

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
};
