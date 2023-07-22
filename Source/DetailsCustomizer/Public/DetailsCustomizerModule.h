// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "PropertyEditorModule.h"

//class DETAILSCUSTOMIZER_API FDetailsCustomizerModule : public FPropertyEditorModule
class FDetailsCustomizerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

