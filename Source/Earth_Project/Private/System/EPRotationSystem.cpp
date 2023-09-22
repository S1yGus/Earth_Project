// Earth_Project, All rights reserved.

#include "System/EPRotationSystem.h"
#include "Components/BillboardComponent.h"
#include "EPGameMode.h"
#include "Actors/EPSun.h"
#include "Actors/EPMoon.h"
#include "TimeConstance.h"

using namespace TimeConstance;

constexpr static float MaxSunAngle = 23.5f;
constexpr static float MaxMoonAngle = 28.7f;
constexpr static float MoonRotationOffset = 0.0366f;

AEPRotationSystem::AEPRotationSystem()
{
    PrimaryActorTick.bCanEverTick = false;

    BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("BillboardComponent");
    SetRootComponent(BillboardComponent);
}

void AEPRotationSystem::BeginPlay()
{
    Super::BeginPlay();

    check(BillboardComponent);
    check(Sun);
    check(Moon);

    if (const auto GameMode = GetGameMode())
    {
        GameMode->OnTimeChanged.AddUObject(this, &ThisClass::OnTimeChanged);
    }
}

AEPGameMode* AEPRotationSystem::GetGameMode() const
{
    return GetWorld()->GetAuthGameMode<AEPGameMode>();
}

void AEPRotationSystem::OnTimeChanged(float Time)
{
    UpdateSunRotation();
    UpdateMoonRotation();
}

void AEPRotationSystem::UpdateSunRotation()
{
    const auto GameMode = GetGameMode();
    if (!Sun || !GameMode)
        return;

    // Angle for sun daily movements.
    const auto DayNewYaw = FMath::GetMappedRangeValueClamped(TRange<float>{0.0f, static_cast<float>(HoursInDay)},    //
                                                             TRange<float>{0.0f, 360.0f},                            //
                                                             GameMode->GetCurrentHour());
    // Angle for sun simplified yearly movements.
    const auto YearNewYaw = FMath::GetMappedRangeValueClamped(TRange<float>{0.0f, static_cast<float>(DaysInYear)},    //
                                                              TRange<float>{360.0f, 0.0f},                            //
                                                              GameMode->GetCurrentDay());
    const auto DayNewPitch = FMath::Sin(FMath::DegreesToRadians(YearNewYaw)) * MaxSunAngle;

    Sun->SetActorRotation(FRotator{DayNewPitch, DayNewYaw, 0.0f});
}

void AEPRotationSystem::UpdateMoonRotation()
{
    const auto GameMode = GetGameMode();
    if (!Moon || !GameMode)
        return;

    // Angles for moon simplified daily movements.
    static float BeginOfCircle = 0.0f;
    static float EndOfCircle = 360.0f + MoonRotationOffset;

    const auto NewYaw = FMath::GetMappedRangeValueClamped(TRange<float>{0.0f, static_cast<float>(HoursInDay)},    //
                                                          TRange<float>{EndOfCircle, BeginOfCircle},              //
                                                          GameMode->GetCurrentHour());
    const auto NewPitch = FMath::Sin(FMath::DegreesToRadians(NewYaw)) * MaxMoonAngle;

    Moon->SetActorRotation(FRotator{NewPitch, NewYaw, 0.0f});

    static const float Tolerance = 1.0e-4f;
    if (FMath::IsNearlyEqual(NewYaw, BeginOfCircle, Tolerance))
    {
        BeginOfCircle += MoonRotationOffset;
        EndOfCircle += MoonRotationOffset;
    }
}
