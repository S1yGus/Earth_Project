// Earth_Project, All rights reserved.

#include "Settings/EPFloatSetting.h"

float UEPFloatSetting::GetCurrentValue() const
{
    if (!Getter)
        return 0.0f;

    return Getter();
}

void UEPFloatSetting::SetValue(float NewValue)
{
    if (!Setter)
        return;

    Setter(NewValue);
}
