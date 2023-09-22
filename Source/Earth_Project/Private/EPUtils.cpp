#include "EPUtils.h"

FText EPUtils::FormatTextFromInt(int32 InValue, int32 MinLen, TCHAR FillChar)
{
    FString ResultStr = FString::FromInt(InValue);
    const auto ToAdd = MinLen - ResultStr.Len();
    if (ToAdd > 0)
    {
        ResultStr = FString::ChrN(ToAdd, FillChar).Append(ResultStr);
    }

    return FText::FromString(ResultStr);
}
