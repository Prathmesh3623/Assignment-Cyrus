// Copyright Epic Games, Inc. All Rights Reserved.


#include "CyrusAssignmentPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "CyrusAssignmentCameraManager.h"

ACyrusAssignmentPlayerController::ACyrusAssignmentPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ACyrusAssignmentCameraManager::StaticClass();
}

void ACyrusAssignmentPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
