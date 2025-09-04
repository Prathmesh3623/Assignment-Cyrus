// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BoxData.h" 
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

class UShooterUI;

/**
 *  Simple GameMode for a first person shooter game
 *  Manages game UI
 *  Keeps track of team scores
 */
UCLASS(abstract)
class CYRUSASSIGNMENT_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	/** Type of UI widget to spawn */
	//UPROPERTY(EditAnywhere, Category="Shooter")
	//TSubclassOf<UShooterUI> ShooterUIClass;


	/** Pointer to the UI widget */
	//TObjectPtr<UShooterUI> ShooterUI;

	
	/** Map of scores by team ID */
	TMap<uint8, int32> TeamScores;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UShooterWidget> ShooterWidgetClass;

	UPROPERTY()
	UShooterWidget* ShooterWidget;
public:
	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Points);

protected:

	/** Gameplay initialization */
	virtual void BeginPlay() override;
	

private:
	int32 TotalScore = 0;

public:

	/** Increases the score for the given team */
	void IncrementTeamScore(uint8 TeamByte);
private:
	void SpawnBoxes(const FBoxDataRoot& Data);
	void FetchOnlineBoxData();
};
