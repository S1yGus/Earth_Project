// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPMoon.generated.h"

class UBillboardComponent;

UCLASS()
class EARTH_PROJECT_API AEPMoon : public AActor
{
    GENERATED_BODY()

public:
    AEPMoon();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBillboardComponent* BillboardComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* MoonMeshComponent;

    virtual void BeginPlay() override;
};
