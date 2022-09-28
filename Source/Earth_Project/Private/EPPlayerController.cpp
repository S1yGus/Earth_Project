// Earth_Project, All rights reserved.

#include "EPPlayerController.h"

void AEPPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent);

    InputComponent->BindAction("Enter", EInputEvent::IE_Pressed, this, &ThisClass::OnPressedEnter).bExecuteWhenPaused = true;
    InputComponent->BindAction("Esc", EInputEvent::IE_Pressed, this, &ThisClass::OnPressedEscape).bExecuteWhenPaused = true;
}

void AEPPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(true));
    bShowMouseCursor = true;
}

void AEPPlayerController::OnPressedEnter()
{
    OnPressedEnt.Broadcast();
}

void AEPPlayerController::OnPressedEscape()
{
    OnPressedEsc.Broadcast();
}
