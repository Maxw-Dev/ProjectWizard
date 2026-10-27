// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectWizardPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ProjectWizardCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "ProjectWizard.h"
#include "Widgets/Input/SVirtualJoystick.h"

AProjectWizardPlayerController::AProjectWizardPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AProjectWizardCameraManager::StaticClass();
}

void AProjectWizardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogProjectWizard, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AProjectWizardPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

bool AProjectWizardPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
