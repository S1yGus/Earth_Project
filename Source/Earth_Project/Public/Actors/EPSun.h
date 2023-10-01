// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPSun.generated.h"

class UDirectionalLightComponent;
class UBillboardComponent;

UCLASS()
class EARTH_PROJECT_API AEPSun : public AActor
{
    GENERATED_BODY()

public:
    AEPSun();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> BillboardComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> SunMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UDirectionalLightComponent> DirectionalLightComponent;
};
