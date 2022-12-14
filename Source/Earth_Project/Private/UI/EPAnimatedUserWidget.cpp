// Earth_Project, All rights reserved.

#include "UI/EPAnimatedUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "EPGameMode.h"

void UEPAnimatedUserWidget::ShowStartupAnimation()
{
    PlayAnimation(StartupAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartupSound);
}

void UEPAnimatedUserWidget::ShowFadeoutAnimation()
{
    PlayAnimation(FadeoutAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), FadeoutSound);
}

void UEPAnimatedUserWidget::SetGameState(EGameState NewGameState)
{
    const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>();
    if (!GameMode)
        return;

    GameMode->SetGameState(NewGameState);
}
