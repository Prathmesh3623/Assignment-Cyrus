// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterWidget.h"
#include "Components/TextBlock.h"

void UShooterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (!ScoreText)
    {
        UE_LOG(LogTemp, Error, TEXT("ScoreText is NULL in NativeConstruct"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("ShooterWidget::NativeConstruct - ScoreText is valid"));
    ScoreText->SetText(FText::FromString(TEXT("Score: 0")));
}

void UShooterWidget::UpdateScore(int32 NewScore)
{
    if (!ScoreText)
    {
        UE_LOG(LogTemp, Error, TEXT("ScoreText is NULL in UpdateScore"));
        return;
    }

    ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore)));
}

