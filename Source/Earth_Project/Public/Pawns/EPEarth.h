// Earth_Project, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EPCoreTypes.h"
#include "EPEarth.generated.h"

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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> EarthMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> CloudsMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> AtmosphereMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clouds")
    float CloudsRotationSpeed{0.001f};

    virtual void BeginPlay() override;

private:
    bool bCanRotate{false};
    bool bAllowInput{false};
    float TargetArmLength{0};
    FTimerHandle CloudsRotationTimerHandle;
    FTimerHandle ZoomTimerHandle;

    void Setup();

    void AllowRotation(bool bInCanRotate) { bCanRotate = bInCanRotate; }
    void LookX(float Amount);
    void LookY(float Amount);
    void Zoom(float ZoomDelta);

    void OnCloudsRotation();
    void OnZoom();
    void OnGameStateChanged(EGameState NewGameState);
    void OnAspectRatioChanged(const FAspectRatioData& NewAspectRatioData);
};
