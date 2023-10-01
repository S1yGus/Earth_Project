// Earth_Project, All rights reserved.

#include "UI/Menu/EPComboBoxSettingUserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/TextBlock.h"
#include "Settings/EPIntSetting.h"

void UEPComboBoxSettingUserWidget::Init(UEPIntSetting* NewSetting)
{
    if (!NewSetting)
        return;

    Setting = NewSetting;
    SettingNameText->SetText(Setting->GetName());

    Update();
}

void UEPComboBoxSettingUserWidget::Update()
{
    if (!Setting)
        return;

    SettingComboBox->ClearOptions();
    for (const auto& Option : Setting->GetOptions())
    {
        SettingComboBox->AddOption(Option.ToString());
    }

    const int32 CurrentValue = Setting->GetCurrentValue();
    if (CurrentValue != INDEX_NONE)
    {
        SettingComboBox->SetSelectedIndex(CurrentValue);
    }

    SettingComboBox->SetIsEnabled(CurrentValue != INDEX_NONE);
}

void UEPComboBoxSettingUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    check(SettingNameText);
    check(SettingComboBox);

    SettingComboBox->OnSelectionChanged.AddDynamic(this, &ThisClass::OnSelectionChanged);
}

void UEPComboBoxSettingUserWidget::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (SelectionType == ESelectInfo::Direct || !Setting)
        return;

    Setting->SetValue(SettingComboBox->FindOptionIndex(SelectedItem));
}
