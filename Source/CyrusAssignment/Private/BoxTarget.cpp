#include "BoxTarget.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Variant_Shooter/ShooterGameMode.h"

ABoxTarget::ABoxTarget()
{
    
    PrimaryActorTick.bCanEverTick = false;

    // Create mesh component
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
    RootComponent = Mesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        Mesh->SetStaticMesh(CubeMesh.Object);
    }

    Mesh->SetMobility(EComponentMobility::Movable);
}

void ABoxTarget::InitBox(const FBoxType& Type, const FBoxTransform& Transform)
{
    SetActorLocation(Transform.Location);
    SetActorRotation(Transform.Rotation);
    SetActorScale3D(Transform.Scale);

    // Set color using dynamic material
    UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/Variant_Shooter/M_BoxDynamic.M_BoxDynamic'"));
    if (BaseMaterial && Mesh)
    {
        UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
        if (DynMat)
        {
            DynMat->SetVectorParameterValue("BaseColor", Type.Color);
            Mesh->SetMaterial(0, DynMat);
        }
    }

    // Set properties from JSON type
    Health = Type.Health;
    ScoreValue = Type.Score;

    UE_LOG(LogTemp, Warning, TEXT("Box '%s' spawned with %d health and %d score"),
        *Type.Name, Health, ScoreValue);
}

void ABoxTarget::ApplyDamage(int32 Amount)
{
    Health -= Amount;
    UE_LOG(LogTemp, Warning, TEXT("%s box took %d damage, health now %d"), *GetName(), Amount, Health);

    if (Health <= 0)
    {
        HandleDestruction();
    }
}

void ABoxTarget::HandleDestruction()
{
    // Award score to GameMode
    AShooterGameMode* GameMode = Cast<AShooterGameMode>(UGameplayStatics::GetGameMode(this));
    if (GameMode)
    {
        GameMode->AddScore(ScoreValue);
        UE_LOG(LogTemp, Warning, TEXT("Awarded %d score to player"), ScoreValue);
    }

    // Optional explosion effect
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    }

    Destroy();
}
void ABoxTarget::BeginPlay()
{
    Super::BeginPlay();

    // Optional: add logs, effects, initialization here
    //UE_LOG(LogTemp, Log, TEXT("BoxTarget::BeginPlay called."));
}