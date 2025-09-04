// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxData.h"

class FBoxDataLoader
{
public:
    
    static bool ParseFromString(const FString& JsonString, FBoxDataRoot& OutData);
};
