// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Settings/EPSetting.h"
#include "EPFloatSetting.generated.h"

UCLASS()
class EARTH_PROJECT_API UEPFloatSetting : public UEPSetting
{
    GENERATED_BODY()

public:
    float GetCurrentValue() const;
    void SetValue(float NewValue);

private:
    TFunction<float()> Getter;
    TFunction<void(float)> Setter;

    void AddGetter(TFunction<float()> Func) { Getter = Func; }
    void AddSetter(TFunction<void(float)> Func) { Setter = Func; }

    friend class UEPGameUserSettings;
};
