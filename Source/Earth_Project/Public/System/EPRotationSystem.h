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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBillboardComponent> BillboardComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeSystem")
    TObjectPtr<AEPSun> Sun;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeSystem")
    TObjectPtr<AEPMoon> Moon;

    virtual void BeginPlay() override;

private:
    FORCEINLINE AEPGameMode* GetGameMode() const;

    void OnTimeChanged(float Seconds);

    void UpdateSunRotation();
    void UpdateMoonRotation();
};
