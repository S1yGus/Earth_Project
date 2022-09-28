// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/EPSettingWidgetInterface.h"
#include "EPComboBoxSettingUserWidget.generated.h"

class UComboBoxString;
class UEPIntSetting;
class UTextBlock;

UCLASS()
class EARTH_PROJECT_API UEPComboBoxSettingUserWidget : public UUserWidget, public IEPSettingWidgetInterface
{
    GENERATED_BODY()

public:
    void Init(UEPIntSetting* NewSetting);
    virtual void Update() override;

protected:
    UPROPERTY(Meta = (BindWidget))
    UTextBlock* SettingNameText;

    UPROPERTY(Meta = (BindWidget))
    UComboBoxString* SettingComboBox;

    UPROPERTY()
    UEPIntSetting* Setting;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};
