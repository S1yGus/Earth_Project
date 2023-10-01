// Earth_Project, All rights reserved.

#include "Actors/EPMoon.h"
#include "Components/BillboardComponent.h"

AEPMoon::AEPMoon()
{
    PrimaryActorTick.bCanEverTick = false;

    BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("Billboard");
    check(BillboardComponent);
    SetRootComponent(BillboardComponent);

    MoonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Moon");
    check(MoonMeshComponent);
    MoonMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MoonMeshComponent->CastShadow = false;
    MoonMeshComponent->SetRelativeLocation(FVector(-30000000.0f, 0.0f, 0.0f));
    MoonMeshComponent->SetRelativeScale3D(FVector(10000.0f, 10000.0f, 10000.0f));
    MoonMeshComponent->SetupAttachment(GetRootComponent());
}
