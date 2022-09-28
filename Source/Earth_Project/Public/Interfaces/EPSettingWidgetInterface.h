// Earth_Project, All rights reserved.

#pragma once

#include "EPSettingWidgetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEPSettingWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

class IEPSettingWidgetInterface
{
    GENERATED_BODY()

public:
    virtual void Update() = 0;
};
