// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonoursProjGameMode.h"
#include "HonoursProjPlayerController.h"
#include "HonoursProjPawn.h"

//#include "DetailsCustomizer/Public/DetailsCustomizerModule.h"


AHonoursProjGameMode::AHonoursProjGameMode()
{
	// no pawn by default
	DefaultPawnClass = AHonoursProjPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AHonoursProjPlayerController::StaticClass();

	//FDetailsCustomizerModule& PropertyModule = FModuleManager::LoadModuleChecked<FDetailsCustomizerModule>("DetailsCustomizer");

}
