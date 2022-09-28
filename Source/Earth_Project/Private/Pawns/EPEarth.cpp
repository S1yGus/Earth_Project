// Earth_Project, All rights reserved.

#include "Pawns/EPEarth.h"
#include "Components/SkyAtmosphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Settings/EPGameUserSettings.h"
#include "EPGameMode.h"

constexpr static float MinArmLength = 24000000.0f;
constexpr static float MaxArmLength = 36000000.0f;
constexpr static float ZoomStep = 1000000.0f;
constexpr static float ZoomTimerRate = 0.016f;
constexpr static int32 ZoomInterpSpeed = 12;

AEPEarth::AEPEarth()
{
    PrimaryActorTick.bCanEverTick = false;

    SkyAtmosphereComponent = CreateDefaultSubobject<USkyAtmosphereComponent>("Atmosphere");
    SkyAtmosphereComponent->BottomRadius = 100.0f;
    SkyAtmosphereComponent->RayleighExponentialDistribution = 2.0f;

    EarthMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Earth");
    EarthMeshComponent->CastShadow = false;
    EarthMeshComponent->SetRelativeLocation(FVector{0.0f, 0.0f, -10000000.0f});
    EarthMeshComponent->SetRelativeScale3D(FVector{10000.0f});
    EarthMeshComponent->SetupAttachment(SkyAtmosphereComponent);

    CloudsMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Clouds");
    CloudsMeshComponent->CastShadow = false;
    CloudsMeshComponent->SetRelativeLocation(FVector{0.0f, 0.0f, -10000000.0f});
    CloudsMeshComponent->SetRelativeScale3D(FVector{10150.0f});
    CloudsMeshComponent->SetupAttachment(SkyAtmosphereComponent);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(EarthMeshComponent);
    SpringArmComponent->TargetArmLength = 30000000.0f;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->bConstrainAspectRatio = true;

    SetRootComponent(SkyAtmosphereComponent);
}

void AEPEarth::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("LookX", this, &ThisClass::LookX);
    PlayerInputComponent->BindAxis("LookY", this, &ThisClass::LookY);

    DECLARE_DELEGATE_OneParam(FOnRotationSignature, bool);
    PlayerInputComponent->BindAction<FOnRotationSignature>("AllowRotation", IE_Pressed, this, &ThisClass::AllowRotation, true);
    PlayerInputComponent->BindAction<FOnRotationSignature>("AllowRotation", IE_Released, this, &ThisClass::AllowRotation, false);

    DECLARE_DELEGATE_OneParam(FOnZoomSignature, float);
    PlayerInputComponent->BindAction<FOnZoomSignature>("ZoomIn", IE_Pressed, this, &ThisClass::Zoom, ZoomStep);
    PlayerInputComponent->BindAction<FOnZoomSignature>("ZoomOut", IE_Pressed, this, &ThisClass::Zoom, -ZoomStep);
}

void AEPEarth::BeginPlay()
{
    Super::BeginPlay();

    check(SkyAtmosphereComponent);
    check(EarthMeshComponent);
    check(CloudsMeshComponent);
    check(SpringArmComponent);
    check(CameraComponent);

    Setup();
}

void AEPEarth::Setup()
{
    TargetArmLength = SpringArmComponent->TargetArmLength;

    if (const auto GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->OnAspectRatioChanged.AddUObject(this, &ThisClass::OnAspectRatioChanged);
        OnAspectRatioChanged(GameUserSettings->GetAspectRatio());    // Aspect ratio initialization.
    }

    if (const auto GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
    }
}

void AEPEarth::LookX(float Amount)
{
    if (!bAllowInput || !bCanRotate || !Amount || !Controller)
        return;

    SpringArmComponent->AddWorldRotation(FRotator{0.0f, Amount, 0.0f});
}

void AEPEarth::LookY(float Amount)
{
    if (!bAllowInput || !bCanRotate || !Amount || !Controller)
        return;

    SpringArmComponent->AddLocalRotation(FRotator{Amount, 0.0f, 0.0f});
}

void AEPEarth::Zoom(float ZoomDelta)
{
    if (!bAllowInput)
        return;

    TargetArmLength = FMath::Clamp(TargetArmLength + ZoomDelta, MinArmLength, MaxArmLength);

    if (!ZoomTimerHandle.IsValid())
    {
        GetWorldTimerManager().SetTimer(ZoomTimerHandle, this, &ThisClass::OnZoom, ZoomTimerRate, true);
    }
}

void AEPEarth::OnZoom()
{
    if (FMath::IsNearlyEqual(SpringArmComponent->TargetArmLength, TargetArmLength))
    {
        GetWorldTimerManager().ClearTimer(ZoomTimerHandle);
        return;
    }

    SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, TargetArmLength, ZoomTimerRate, ZoomInterpSpeed);
}

void AEPEarth::OnGameStateChanged(EGameState NewGameState)
{
    bAllowInput = NewGameState == EGameState::InProgramm;
}

void AEPEarth::OnAspectRatioChanged(const FAspectRatioData& NewAspectRatioData)
{
    CameraComponent->SetAspectRatio(NewAspectRatioData.AspectRatio);
    CameraComponent->SetFieldOfView(NewAspectRatioData.FOV);
}
