// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EPSetting.generated.h"

UCLASS()
class EARTH_PROJECT_API UEPSetting : public UObject
{
    GENERATED_BODY()

public:
    const FText& GetName() const { return Name; }

private:
    FText Name;

    void SetName(const FText& NewName) { Name = NewName; }

    friend class UEPGameUserSettings;
};
