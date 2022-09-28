// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "EPCoreTypes.h"
#include "EPGameUserSettings.generated.h"

class UEPSetting;
class UEPIntSetting;
class UEPFloatSetting;
class UEPSettingsSave;

UCLASS()
class EARTH_PROJECT_API UEPGameUserSettings : public UGameUserSettings
{
    GENERATED_BODY()

public:
    FOnResolutionChangedSignature OnResolutionChanged;
    FOnAspectRatioChangedSignature OnAspectRatioChanged;

    UEPGameUserSettings();

    static UEPGameUserSettings* Get();
    inline const TArray<UEPSetting*>& GetVideoSettings() const { return VideoSettings; }
    inline const TArray<UEPSetting*>& GetSoundSettings() const { return SoundSettings; }
    const FAspectRatioData& GetAspectRatio() const;

    void SetLastConfirmedResolutionSettings();

    void InitSoundVolume();

    virtual void LoadSettings(bool bForceReload = false) override;
    virtual void SaveSettings() override;

private:
    UPROPERTY()
    TArray<UEPSetting*> VideoSettings;
    UPROPERTY()
    UEPIntSetting* ResolutionSetting;
    UPROPERTY()
    TArray<UEPSetting*> SoundSettings;

    UPROPERTY()
    UEPSettingsSave* SettingsSave;

    void InitVideoSettings();
    void InitSoundSettings();

    const TArray<FText> GetScreenResolutions() const;
    void UpdateResolutionSetting();
    void SetAllVideoSettings(int32 NewValue);
    void SetLowestResolution();
    void SetSoundClassVolume(const FString& SoundClassName, float NewVolume);

    void CheckSettingsSave();

    inline UEPIntSetting* CreateIntSetting(const FText& Name, const TArray<FText>& Options, TArray<UEPSetting*>& AddTo);
    inline UEPFloatSetting* CreateFloatSetting(const FText& Name, TArray<UEPSetting*>& AddTo);

    template <class T>
    T* CreateSetting(const FText& Name, TArray<UEPSetting*>& AddTo)
    {
        T* Setting = NewObject<T>();
        checkf(Setting->IsA(UEPSetting::StaticClass()), TEXT("T must be based on UEPSetting"));
        Setting->SetName(Name);
        AddTo.Add(Setting);

        return Setting;
    }
};
