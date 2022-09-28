// Earth_Project, All rights reserved.

#include "EPGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/EPGameUserSettings.h"

void UEPGameInstance::QuitGame(APlayerController* SpecificPlayer)
{
    UKismetSystemLibrary::QuitGame(this, SpecificPlayer, EQuitPreference::Quit, true);
}

void UEPGameInstance::OnStart()
{
    Super::OnStart();

    if (const auto GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->InitSoundVolume();
    }
}
