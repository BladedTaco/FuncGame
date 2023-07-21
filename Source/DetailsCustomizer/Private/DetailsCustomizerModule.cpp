// Copyright Epic Games, Inc. All Rights Reserved.

#include "DetailsCustomizerModule.h"

#define LOCTEXT_NAMESPACE "FDetailsCustomizer"

#include "HonoursProj/Types/Type.h"

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
	

	//// to register our custom property
	//PropertyModule.RegisterCustomPropertyTypeLayout(
	//	// This is the name of the Struct (we can also use "MyStruct" instead)
	//	// this tells the property editor which is the struct property our customization will applied on.
	//	FMyStruct::StaticStruct()->GetFName(),
	//	// this is where our MakeInstance() method is usefull
	//	FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyStructCustomization::MakeInstance));


	//// Custom detail views
	//PropertyModule.RegisterCustomClassLayout(
	//	"Type",
	//	FOnGetDetailCustomizationInstance::CreateStatic(&FTypeDetails::MakeInstance)
	//);
	//PropertyModule.RegisterCustomClassLayout(
	//	"TypeVar",
	//	FOnGetDetailCustomizationInstance::CreateStatic(&FTypeDetails::MakeInstance)
	//);
	//PropertyModule.RegisterCustomClassLayout(
	//	"TypePtr",
	//	FOnGetDetailCustomizationInstance::CreateStatic(&FTypeDetails::MakeInstance)
	//);
	//PropertyModule.RegisterCustomClassLayout(
	//	"BlockFunction",
	//	FOnGetDetailCustomizationInstance::CreateStatic(&FTypeDetails::MakeInstance)
	//);


	// Custom properties
	PropertyModule.RegisterCustomPropertyTypeLayout(
		"Type", 
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FTypeProperty::MakeInstance)
	);

	//// Custom properties
	//PropertyModule.RegisterCustomPropertyTypeLayout(
	//	"TypePtr",
	//	FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FTypeProperty::MakeInstance)
	//);



	PropertyModule.NotifyCustomizationModuleChanged();

}

void FDetailsCustomizerModule::ShutdownModule()
{
	//FPropertyEditorModule::ShutdownModule();
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


#undef LOCTEXT_NAMESPACE
