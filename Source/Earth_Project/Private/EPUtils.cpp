// Earth_Project, All rights reserved.

#include "EPUtils.h"

FText EPUtils::FormatTextFromInt(int32 InValue, int32 MinLen, TCHAR FillChar)
{
    FString ResultStr = FString::FromInt(InValue);
    if (const int32 ToAdd = MinLen - ResultStr.Len(); ToAdd > 0)
    {
        ResultStr = FString::ChrN(ToAdd, FillChar).Append(ResultStr);
    }

    return FText::FromString(ResultStr);
}
