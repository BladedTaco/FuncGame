// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailsCustomizerModule.h"

#define LOCTEXT_NAMESPACE "FDetailsCustomizer"

#include "TypeDetails.h"
#include "TypeProperty.h"


#include "PropertyEditorModule.h"


IMPLEMENT_MODULE(FDetailsCustomizerModule, DetailsCustomizer)



void FDetailsCustomizerModule::StartupModule()
{
	//FPropertyEditorModule::StartupModule();
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	UE_LOG(LogTemp, Warning, TEXT("DetailsCustomizer Loaded"));

	// import the PropertyEditor module...
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	
	// Custom properties
	PropertyModule.RegisterCustomPropertyTypeLayout(
		//UType::StaticClass()->GetFName(), 
		"Type",
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FTypeProperty::MakeInstance)
	);

	PropertyModule.NotifyCustomizationModuleChanged();

}

void FDetailsCustomizerModule::ShutdownModule()
{
	//FPropertyEditorModule::ShutdownModule();
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}


#undef LOCTEXT_NAMESPACE
