// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ProjectWizardCameraManager.generated.h"

/**
 *  Basic First Person camera manager.
 *  Limits min/max look pitch.
 */
UCLASS()
class AProjectWizardCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AProjectWizardCameraManager();
};
