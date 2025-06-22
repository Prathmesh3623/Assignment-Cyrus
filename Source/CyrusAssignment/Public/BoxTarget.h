#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxData.h"
#include "BoxTarget.generated.h"

UCLASS()
class CYRUSASSIGNMENT_API ABoxTarget : public AActor
{
    GENERATED_BODY()

public:
    ABoxTarget();

    // Particle effect on destroy
    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* ExplosionEffect;

    // Called by GameMode to set up the box
    void InitBox(const FBoxType& Type, const FBoxTransform& Transform);

    // Public damage function (called from weapon/projectile)
    void ApplyDamage(int32 Amount);

    // Set by GameMode during spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Properties")
    int32 ScoreValue;

protected:
    virtual void BeginPlay() override;

    // Box mesh
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    // Health is now marked editable for InitBox/use
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Box Properties")
    int32 Health;

    // Handles destruction, score, effects
    void HandleDestruction();
};
