// Earth_Project, All rights reserved.

#include "Actors/EPSun.h"
#include "Components/BillboardComponent.h"
#include "Components/DirectionalLightComponent.h"

AEPSun::AEPSun()
{
    PrimaryActorTick.bCanEverTick = false;

    BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("Billboard");
    check(BillboardComponent);
    SetRootComponent(BillboardComponent);

    DirectionalLightComponent = CreateDefaultSubobject<UDirectionalLightComponent>("DirectionalLight");
    check(DirectionalLightComponent);
    DirectionalLightComponent->SetLightSourceAngle(0.0f);
    DirectionalLightComponent->CastShadows = false;
    DirectionalLightComponent->SetIntensity(3.14f);
    DirectionalLightComponent->bEnableLightShaftOcclusion = true;
    DirectionalLightComponent->bEnableLightShaftBloom = true;
    DirectionalLightComponent->BloomScale = 0.02f;
    DirectionalLightComponent->BloomMaxBrightness = 5.0f;
    DirectionalLightComponent->bAtmosphereSunLight = false;
    DirectionalLightComponent->SetupAttachment(GetRootComponent());

    SunMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Sun");
    check(SunMeshComponent);
    SunMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SunMeshComponent->CastShadow = false;
    SunMeshComponent->SetRelativeLocation(FVector(-500000000.0f, 0.0f, 0.0f));
    SunMeshComponent->SetRelativeScale3D(FVector(170000.0f, 170000.0f, 170000.0f));
    SunMeshComponent->SetupAttachment(GetRootComponent());
}
