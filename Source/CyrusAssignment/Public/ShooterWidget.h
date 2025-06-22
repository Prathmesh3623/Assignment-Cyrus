// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShooterWidget.generated.h"

/**
 * 
 */
UCLASS()
class CYRUSASSIGNMENT_API UShooterWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
    UFUNCTION(BlueprintCallable)
    void UpdateScore(int32 NewScore);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreText;
};
