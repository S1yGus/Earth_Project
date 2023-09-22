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
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBillboardComponent* BillboardComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* SunMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDirectionalLightComponent* DirectionalLightComponent;

    virtual void BeginPlay() override;
};
