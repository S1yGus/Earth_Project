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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> BillboardComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> MoonMeshComponent;
};
