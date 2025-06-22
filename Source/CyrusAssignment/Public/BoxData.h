// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxData.generated.h"

USTRUCT(BlueprintType)
struct FBoxType
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name;

    UPROPERTY(BlueprintReadWrite)
    FLinearColor Color;

    UPROPERTY(BlueprintReadWrite)
    int32 Health;

    UPROPERTY(BlueprintReadWrite)
    int32 Score;
};

USTRUCT(BlueprintType)
struct FBoxTransform
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FVector Location;

    UPROPERTY(BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY(BlueprintReadWrite)
    FVector Scale;
};

USTRUCT(BlueprintType)
struct FBoxObject
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Type;

    UPROPERTY(BlueprintReadWrite)
    FBoxTransform Transform;
};

USTRUCT(BlueprintType)
struct FBoxDataRoot
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TArray<FBoxType> Types;

    UPROPERTY(BlueprintReadWrite)
    TArray<FBoxObject> Objects;
};
