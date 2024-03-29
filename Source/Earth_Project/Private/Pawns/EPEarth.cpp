// Earth_Project, All rights reserved.

#include "Pawns/EPEarth.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Settings/EPGameUserSettings.h"
#include "EPGameMode.h"

constexpr static float MinArmLength{1300000.0f};
constexpr static float MaxArmLength{3500000.0f};
constexpr static float ZoomStep{100000.0f};
constexpr static float ZoomTimerRate{0.016f};
constexpr static float CloudsRotationTimerRate{0.033f};
constexpr static int32 ZoomInterpSpeed{6};

AEPEarth::AEPEarth()
{
    PrimaryActorTick.bCanEverTick = false;

    AtmosphereMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Atmosphere");
    check(AtmosphereMeshComponent);
    AtmosphereMeshComponent->CastShadow = false;
    AtmosphereMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    AtmosphereMeshComponent->SetGenerateOverlapEvents(false);
    AtmosphereMeshComponent->SetRelativeScale3D(FVector{10450.0f});
    AtmosphereMeshComponent->SetupAttachment(GetRootComponent());

    EarthMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Earth");
    check(EarthMeshComponent);
    EarthMeshComponent->CastShadow = false;
    EarthMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    EarthMeshComponent->SetGenerateOverlapEvents(false);
    EarthMeshComponent->SetRelativeScale3D(FVector{10000.0f});
    EarthMeshComponent->SetupAttachment(GetRootComponent());

    CloudsMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Clouds");
    check(CloudsMeshComponent);
    CloudsMeshComponent->CastShadow = false;
    CloudsMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CloudsMeshComponent->SetGenerateOverlapEvents(false);
    CloudsMeshComponent->SetRelativeScale3D(FVector{10080.0f});
    CloudsMeshComponent->SetupAttachment(GetRootComponent());

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    check(SpringArmComponent);
    SpringArmComponent->TargetArmLength = 2000000.0f;
    SpringArmComponent->SetupAttachment(EarthMeshComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    check(CameraComponent);
    CameraComponent->bConstrainAspectRatio = true;
    CameraComponent->SetupAttachment(SpringArmComponent);
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

    Setup();
    GetWorldTimerManager().SetTimer(CloudsRotationTimerHandle, this, &ThisClass::OnCloudsRotation, CloudsRotationTimerRate, true);
}

void AEPEarth::Setup()
{
    TargetArmLength = SpringArmComponent->TargetArmLength;

    if (auto* GameUserSettings = UEPGameUserSettings::Get())
    {
        GameUserSettings->OnAspectRatioChanged.AddUObject(this, &ThisClass::OnAspectRatioChanged);
        OnAspectRatioChanged(GameUserSettings->GetAspectRatio());    // Aspect ratio initialization.
    }

    if (GetWorld())
    {
        if (auto* GameMode = GetWorld()->GetAuthGameMode<AEPGameMode>())
        {
            GameMode->OnGameStateChanged.AddUObject(this, &ThisClass::OnGameStateChanged);
        }
    }
}

void AEPEarth::LookX(float Amount)
{
    if (!bAllowInput || !bCanRotate || !Amount)
        return;

    SpringArmComponent->AddWorldRotation(FRotator{0.0, Amount, 0.0});
}

void AEPEarth::LookY(float Amount)
{
    if (!bAllowInput || !bCanRotate || !Amount)
        return;

    SpringArmComponent->AddLocalRotation(FRotator{Amount, 0.0, 0.0});
}

void AEPEarth::Zoom(float ZoomDelta)
{
    if (!bAllowInput)
        return;

    TargetArmLength = FMath::Clamp(TargetArmLength + ZoomDelta, MinArmLength, MaxArmLength);
    if (!GetWorldTimerManager().IsTimerActive(ZoomTimerHandle))
    {
        GetWorldTimerManager().SetTimer(ZoomTimerHandle, this, &ThisClass::OnZoom, ZoomTimerRate, true);
    }
}

void AEPEarth::OnCloudsRotation()
{
    CloudsMeshComponent->AddRelativeRotation(FRotator{0.0, CloudsRotationSpeed, 0.0});
}

void AEPEarth::OnZoom()
{
    if (FMath::IsNearlyEqual(SpringArmComponent->TargetArmLength, TargetArmLength))
    {
        GetWorldTimerManager().ClearTimer(ZoomTimerHandle);
    }
    else
    {
        SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, TargetArmLength, ZoomTimerRate, ZoomInterpSpeed);
    }
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
