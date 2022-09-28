// Earth_Project, All rights reserved.

#include "Settings/EPIntSetting.h"

int32 UEPIntSetting::GetCurrentValue() const
{
    if (!Getter)
        return INDEX_NONE;

    return Getter();
}

void UEPIntSetting::SetValue(int32 NewValue)
{
    if (!Setter)
        return;

    Setter(NewValue);
}
