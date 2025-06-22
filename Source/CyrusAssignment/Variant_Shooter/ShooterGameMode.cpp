// Copyright Epic Games, Inc. All Rights Reserved.

#include "Variant_Shooter/ShooterGameMode.h"
#include "ShooterUI.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "BoxDataLoader.h"
#include "BoxData.h"
#include "BoxTarget.h"
#include "ShooterWidget.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// create the UI
	//ShooterUI = CreateWidget<UShooterUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ShooterUIClass);
	//ShooterUI->AddToViewport(0);

	FBoxDataRoot Data;
	if (FBoxDataLoader::LoadBoxData(Data))
	{
		for (const FBoxObject& Obj : Data.Objects)
		{
			const FBoxType* TypePtr = Data.Types.FindByPredicate([&](const FBoxType& T) {
				return T.Name == Obj.Type;
				});

			if (TypePtr)
			{
				FTransform SpawnTransform;
				SpawnTransform.SetLocation(Obj.Transform.Location);
				SpawnTransform.SetRotation(Obj.Transform.Rotation.Quaternion());
				SpawnTransform.SetScale3D(Obj.Transform.Scale);

				ABoxTarget* Box = GetWorld()->SpawnActor<ABoxTarget>(ABoxTarget::StaticClass(), SpawnTransform);

				if (Box)
				{
					// Initialize properties from the matched type
					Box->InitBox(*TypePtr, Obj.Transform);

					// Explicitly set ScoreValue in case InitBox doesn't
					Box->ScoreValue = TypePtr->Score;

					UE_LOG(LogTemp, Log, TEXT("Spawned box [%s] with ScoreValue = %d"), *Obj.Type, TypePtr->Score);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to spawn ABoxTarget of type %s"), *Obj.Type);
				}
			}
		}
	}


	if (!ShooterWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ShooterWidgetClass is NULL!"));
		return;
	}

	ShooterWidget = CreateWidget<UShooterWidget>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		ShooterWidgetClass
	);

	if (!ShooterWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("ShooterWidget creation failed!"));
		return;
	}

	ShooterWidget->AddToViewport();
	ShooterWidget->UpdateScore(0);
	UE_LOG(LogTemp, Warning, TEXT("ShooterWidget created and added to viewport"));
}

void AShooterGameMode::IncrementTeamScore(uint8 TeamByte)
{
	// retrieve the team score if any
	int32 Score = 0;
	if (int32* FoundScore = TeamScores.Find(TeamByte))
	{
		Score = *FoundScore;
	}

	// increment the score for the given team
	TeamScores.Add(TeamByte, Score + 1);

	// update the UI
	//ShooterUI->BP_UpdateScore(TeamByte, Score);
}
void AShooterGameMode::AddScore(int32 Points)
{
	TotalScore += Points;

	if (ShooterWidget)
	{
		ShooterWidget->UpdateScore(TotalScore);
	}
}