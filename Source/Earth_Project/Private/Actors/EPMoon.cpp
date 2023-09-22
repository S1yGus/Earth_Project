// Earth_Project, All rights reserved.

#include "Actors/EPMoon.h"
#include "Components/BillboardComponent.h"

AEPMoon::AEPMoon()
{
    PrimaryActorTick.bCanEverTick = false;

    BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("Billboard");
    SetRootComponent(BillboardComponent);

    MoonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Moon");
    MoonMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MoonMeshComponent->CastShadow = false;
    MoonMeshComponent->SetRelativeLocation(FVector(-30000000.0f, 0.0f, 0.0f));
    MoonMeshComponent->SetRelativeScale3D(FVector(10000.0f, 10000.0f, 10000.0f));
    MoonMeshComponent->SetupAttachment(GetRootComponent());
}

void AEPMoon::BeginPlay()
{
    Super::BeginPlay();

    check(BillboardComponent);
    check(MoonMeshComponent);
}
