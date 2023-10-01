// Earth_Project, All rights reserved.

#include "Settings/EPGameUserSettings.h"
#include "Settings/EPSetting.h"
#include "Settings/EPIntSetting.h"
#include "Settings/EPFloatSetting.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Saves/EPSettingsSave.h"
#include "AudioDevice.h"
#include "AudioThread.h"
#include "Settings/EPSettingsConstants.h"

using namespace SettingsConstants;

#define LOCTEXT_NAMESPACE "GameUserSettings"

#define BIND_SOUND_GETTER(VolumeType)                  \
    [&]()                                              \
    {                                                  \
        return SettingsSave->SoundSettings.VolumeType; \
    }

#define BIND_SOUND_SETTER(SCName, VolumeType)              \
    [&](float NewValue)                                    \
    {                                                      \
        SetSoundClassVolume(SCName, NewValue);             \
        SettingsSave->SoundSettings.VolumeType = NewValue; \
    }

static bool operator==(const FText& LHS, const FText& RHS)
{
    return LHS.ToString() == RHS.ToString();
}

static bool operator==(const FCultureData& Data, const FString& Str)
{
    return Data.Culture == Str;
}

UEPGameUserSettings::UEPGameUserSettings()
{
    InitVideoSettings();
    InitSoundSettings();
}

UEPGameUserSettings* UEPGameUserSettings::Get()
{
    return GEngine ? Cast<UEPGameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

const FAspectRatioData& UEPGameUserSettings::GetAspectRatio() const
{
    return SettingsSave->VideoSettings.AspectRatioData;
}

void UEPGameUserSettings::SetLastConfirmedResolutionSettings()
{
    SetFullscreenMode(GetLastConfirmedFullscreenMode());
    SetScreenResolution(GetLastConfirmedScreenResolution());
    ApplyResolutionSettings(false);
    UpdateResolutionSetting();
}

void UEPGameUserSettings::InitSoundVolume()
{
    SetSoundClassVolume(SCMasterName, SettingsSave->SoundSettings.MasterVolume);
    SetSoundClassVolume(SCUIName, SettingsSave->SoundSettings.UIVolume);
    SetSoundClassVolume(SCFXName, SettingsSave->SoundSettings.FXVolume);
    SetSoundClassVolume(SCMusicName, SettingsSave->SoundSettings.MusicVolume);
}

void UEPGameUserSettings::LoadSettings(bool bForceReload)
{
    Super::LoadSettings(bForceReload);

    CheckSettingsSave();
}

void UEPGameUserSettings::SaveSettings()
{
    Super::SaveSettings();

    UGameplayStatics::SaveGameToSlot(SettingsSave, SettingsSaveSlotName, 0);
}

void UEPGameUserSettings::InitVideoSettings()
{
    {
        auto* Setting = CreateIntSetting(LOCTEXT("ScreenMode_Loc", "Screen mode"), FullscreenOptions, VideoSettings);
        Setting->AddGetter(
            [&]()
            {
                return static_cast<int32>(GetFullscreenMode());
            });
        Setting->AddSetter(
            [&](int32 NewValue)
            {
                SetFullscreenMode(static_cast<EWindowMode::Type>(NewValue));
                ApplyResolutionSettings(false);
                SetLowestResolution();
            });
    }

    {
        ResolutionSetting = CreateIntSetting(LOCTEXT("Resolution_Loc", "Resolution"), GetScreenResolutions(), VideoSettings);
        ResolutionSetting->AddGetter(
            [&]() -> int32
            {
                if (GetFullscreenMode() == EWindowMode::WindowedFullscreen)
                {
                    return INDEX_NONE;
                }
                const FIntPoint CurrentResolution = GetScreenResolution();
                const auto Option = FText::FromString(FString::Printf(TEXT("%d x %d"), CurrentResolution.X, CurrentResolution.Y));
                return ResolutionSetting->GetOptions().IndexOfByKey(Option);
            });
        ResolutionSetting->AddSetter(
            [&](int32 NewValue)
            {
                FString LeftS, RightS;
                if (ResolutionSetting->GetOptions()[NewValue].ToString().Split(" x ", &LeftS, &RightS))
                {
                    const FIntPoint NewResolution{FCString::Atoi(*LeftS), FCString::Atoi(*RightS)};
                    SetScreenResolution(NewResolution);
                    ApplyResolutionSettings(false);
                    OnResolutionChanged.Broadcast();
                }
            });
    }

    {
        auto* Setting = CreateIntSetting(LOCTEXT("VSync_Loc", "V-Sync"), VSyncOptions, VideoSettings);
        Setting->AddGetter(
            [&]()
            {
                return static_cast<int32>(IsVSyncEnabled());
            });
        Setting->AddSetter(
            [&](int32 NewValue)
            {
                SetVSyncEnabled(static_cast<bool>(NewValue));
                ApplyNonResolutionSettings();
            });
    }

    {
        auto* Setting = CreateIntSetting(LOCTEXT("FramerateLimit_Loc", "Framerate limit"), FramerateOptions, VideoSettings);
        Setting->AddGetter(
            [&]()
            {
                return GetFrameRateLimit() == 0.0f ? 0    //
                                                   : FramerateOptions.IndexOfByKey(FText::AsNumber(static_cast<int32>(GetFrameRateLimit())));
            });
        Setting->AddSetter(
            [&](int32 NewValue)
            {
                SetFrameRateLimit(NewValue == 0 ? 0.0f    //
                                                : FCString::Atof(*FramerateOptions[NewValue].ToString()));
                ApplyNonResolutionSettings();
            });
    }

    {
        TArray<FText> AspectRatioOptions;
        for (const auto& Data : AspectRatioData)
        {
            AspectRatioOptions.Add(Data.DisplayName);
        }

        auto* Setting = CreateIntSetting(LOCTEXT("AspectRatio_Loc", "Aspect ratio"), AspectRatioOptions, VideoSettings);
        Setting->AddGetter(
            [&, AspectRatioOptions]() -> int32
            {
                if (GetFullscreenMode() == EWindowMode::Windowed || GetFullscreenMode() == EWindowMode::WindowedFullscreen)
                {
                    return INDEX_NONE;
                }
                return AspectRatioOptions.IndexOfByKey(SettingsSave->VideoSettings.AspectRatioData.DisplayName);
            });
        Setting->AddSetter(
            [&](int32 NewValue)
            {
                SettingsSave->VideoSettings.AspectRatioData = AspectRatioData[NewValue];
                OnAspectRatioChanged.Broadcast(AspectRatioData[NewValue]);
            });
    }

    {
        auto* Setting = CreateIntSetting(LOCTEXT("GraphicsQuality_Loc", "Quality"), GraphicsQualityOptions, VideoSettings);
        Setting->AddGetter(
            [&]()
            {
                return GetAntiAliasingQuality();    // All video settings have the same index.
            });
        Setting->AddSetter(
            [&](int32 NewValue)
            {
                SetAllVideoSettings(NewValue);
                ApplyNonResolutionSettings();
            });
    }
}

void UEPGameUserSettings::InitSoundSettings()
{
    {
        auto* Setting = CreateFloatSetting(LOCTEXT("MasterVolume_Loc", "Master"), SoundSettings);
        Setting->AddGetter(BIND_SOUND_GETTER(MasterVolume));
        Setting->AddSetter(BIND_SOUND_SETTER(SCMasterName, MasterVolume));
    }

    {
        auto* Setting = CreateFloatSetting(LOCTEXT("UIVolume_Loc", "Interface"), SoundSettings);
        Setting->AddGetter(BIND_SOUND_GETTER(UIVolume));
        Setting->AddSetter(BIND_SOUND_SETTER(SCUIName, UIVolume));
    }

    {
        auto* Setting = CreateFloatSetting(LOCTEXT("FXVolume_Loc", "Effects"), SoundSettings);
        Setting->AddGetter(BIND_SOUND_GETTER(FXVolume));
        Setting->AddSetter(BIND_SOUND_SETTER(SCFXName, FXVolume));
    }

    {
        auto* Setting = CreateFloatSetting(LOCTEXT("MusicVolume_Loc", "Music"), SoundSettings);
        Setting->AddGetter(BIND_SOUND_GETTER(MusicVolume));
        Setting->AddSetter(BIND_SOUND_SETTER(SCMusicName, MusicVolume));
    }
}

const TArray<FText> UEPGameUserSettings::GetScreenResolutions() const
{
    const EWindowMode::Type ScreenMode = GetFullscreenMode();
    TArray<FIntPoint> Resolutions;
    if (ScreenMode == EWindowMode::Windowed)
    {
        UKismetSystemLibrary::GetConvenientWindowedResolutions(Resolutions);
    }
    else
    {
        UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
    }

    TArray<FText> ResolutionsOptions;
    for (const auto& Resolution : Resolutions)
    {
        ResolutionsOptions.Add(FText::FromString(FString::Printf(TEXT("%d x %d"), Resolution.X, Resolution.Y)));
    }

    return ResolutionsOptions;
}

void UEPGameUserSettings::UpdateResolutionSetting()
{
    ResolutionSetting->SetOptions(GetScreenResolutions());
}

void UEPGameUserSettings::SetAllVideoSettings(int32 NewValue)
{
    SetViewDistanceQuality(NewValue);
    SetAntiAliasingQuality(NewValue);
    SetPostProcessingQuality(NewValue);
    SetShadowQuality(NewValue);
    SetGlobalIlluminationQuality(NewValue);
    SetReflectionQuality(NewValue);
    SetTextureQuality(NewValue);
    SetVisualEffectQuality(NewValue);
    SetFoliageQuality(NewValue);
    SetShadingQuality(NewValue);
}

void UEPGameUserSettings::SetLowestResolution()
{
    UpdateResolutionSetting();

    if (GetFullscreenMode() != EWindowMode::Type::WindowedFullscreen)
    {
        ResolutionSetting->SetValue(0);    // Set the lowest resolution in this screen mode.
    }
    else
    {
        OnResolutionChanged.Broadcast();
    }
}

void UEPGameUserSettings::SetSoundClassVolume(const FString& SoundClassName, float NewVolume)
{
    FAudioThread::RunCommandOnAudioThread(
        [=]()
        {
            if (GEngine)
            {
                const FAudioDeviceHandle ADevice = GEngine->GetMainAudioDevice();
                for (const auto& [SoundClass, SoundClassProperties] : ADevice->GetSoundClassPropertyMap())
                {
                    if (SoundClass && SoundClass->GetFullName().Find(SoundClassName) != INDEX_NONE)
                    {
                        SoundClass->Properties.Volume = NewVolume;
                    }
                }
            }
        });
}

void UEPGameUserSettings::CheckSettingsSave()
{
    if (SettingsSave)
        return;

    if (UGameplayStatics::DoesSaveGameExist(SettingsSaveSlotName, 0))
    {
        SettingsSave = Cast<UEPSettingsSave>(UGameplayStatics::LoadGameFromSlot(SettingsSaveSlotName, 0));
    }
    else
    {
        SettingsSave = Cast<UEPSettingsSave>(UGameplayStatics::CreateSaveGameObject(UEPSettingsSave::StaticClass()));
        RunHardwareBenchmark();
        ApplySettings(false);
    }

    check(SettingsSave);
}

UEPIntSetting* UEPGameUserSettings::CreateIntSetting(const FText& Name, const TArray<FText>& Options, TArray<TObjectPtr<UEPSetting>>& AddTo)
{
    auto* Setting = CreateSetting<UEPIntSetting>(Name, AddTo);
    Setting->SetOptions(Options);

    return Setting;
}

UEPFloatSetting* UEPGameUserSettings::CreateFloatSetting(const FText& Name, TArray<TObjectPtr<UEPSetting>>& AddTo)
{
    return CreateSetting<UEPFloatSetting>(Name, AddTo);
}

#undef LOCTEXT_NAMESPACE
