#pragma once

#include "CoreMinimal.h"

class EPUtils
{
public:
    static FText FormatTextFromInt(int32 InValue, int32 MinLen, TCHAR FillChar = ' ');
};
