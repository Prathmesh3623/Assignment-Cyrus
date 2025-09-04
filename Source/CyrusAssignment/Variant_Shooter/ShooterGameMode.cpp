// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGameMode.h"
#include "ShooterWidget.h"
#include "BoxDataLoader.h"
#include "BoxTarget.h"
#include "Kismet/GameplayStatics.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonSerializer.h"

void AShooterGameMode::BeginPlay()
{
    Super::BeginPlay();

    
    FetchOnlineBoxData();

   
    if (ShooterWidgetClass)
    {
        ShooterWidget = CreateWidget<UShooterWidget>(
            UGameplayStatics::GetPlayerController(GetWorld(), 0),
            ShooterWidgetClass
        );
        if (ShooterWidget)
        {
            ShooterWidget->AddToViewport();
            ShooterWidget->UpdateScore(TotalScore);
        }
    }
}

void AShooterGameMode::FetchOnlineBoxData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Req, FHttpResponsePtr Res, bool bSuccess)
        {
            

            FBoxDataRoot Data;
            if (FBoxDataLoader::ParseFromString(Res->GetContentAsString(), Data))
            {
                SpawnBoxes(Data);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to parse online JSON"));
            }
        });

    Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
    Request->SetVerb("GET");
    Request->ProcessRequest();
    UE_LOG(LogTemp, Error, TEXT("Online feyching success"));
}

void AShooterGameMode::IncrementTeamScore(uint8 TeamByte)
{
}

void AShooterGameMode::SpawnBoxes(const FBoxDataRoot& Data)
{
    for (const FBoxObject& Obj : Data.Objects)
    {
        const FBoxType* TypePtr = Data.Types.FindByPredicate(
            [&](const FBoxType& T) { return T.Name == Obj.Type; });

        if (TypePtr)
        {
            FTransform SpawnTransform;
            SpawnTransform.SetLocation(Obj.Transform.Location);
            SpawnTransform.SetRotation(Obj.Transform.Rotation.Quaternion());
            SpawnTransform.SetScale3D(Obj.Transform.Scale);

            ABoxTarget* Box = GetWorld()->SpawnActor<ABoxTarget>(
                ABoxTarget::StaticClass(), SpawnTransform);

            if (Box)
            {
                Box->InitBox(*TypePtr, Obj.Transform);
                Box->ScoreValue = TypePtr->Score;
            }
        }
    }
}

void AShooterGameMode::AddScore(int32 Points)
{
    TotalScore += Points;
    if (ShooterWidget)
    {
        ShooterWidget->UpdateScore(TotalScore);
    }
    UE_LOG(LogTemp, Log, TEXT("Current Score: %d"), TotalScore);
}
