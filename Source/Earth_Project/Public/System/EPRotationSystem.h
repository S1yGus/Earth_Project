// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EPRotationSystem.generated.h"

class UBillboardComponent;
class AEPSun;
class AEPMoon;
class AEPGameMode;

UCLASS()
class EARTH_PROJECT_API AEPRotationSystem : public AActor
{
    GENERATED_BODY()

public:
    AEPRotationSystem();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBillboardComponent* BillboardComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeSystem")
    AEPSun* Sun;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeSystem")
    AEPMoon* Moon;

    virtual void BeginPlay() override;

private:
    inline AEPGameMode* GetGameMode() const;

    void OnTimeChanged(float Time);

    void UpdateSunRotation();
    void UpdateMoonRotation();
};
