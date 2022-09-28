// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EPCoreTypes.h"
#include "EPEarth.generated.h"

class USkyAtmosphereComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class EARTH_PROJECT_API AEPEarth : public APawn
{
    GENERATED_BODY()

public:
    AEPEarth();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkyAtmosphereComponent* SkyAtmosphereComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* EarthMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* CloudsMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    virtual void BeginPlay() override;

private:
    bool bCanRotate = false;
    bool bAllowInput = false;
    float TargetArmLength = 0;
    FTimerHandle ZoomTimerHandle;

    void Setup();

    void AllowRotation(bool bInCanRotate) { bCanRotate = bInCanRotate; }
    void LookX(float Amount);
    void LookY(float Amount);
    void Zoom(float ZoomDelta);

    void OnZoom();
    void OnGameStateChanged(EGameState NewGameState);
    void OnAspectRatioChanged(const FAspectRatioData& NewAspectRatioData);
};
