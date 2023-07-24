// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HUD/EditorUserWidget.h"

#include "FunctionHUD.generated.h"


/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class HONOURSPROJ_API UFunctionHUD : public UEditorUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD Data")
		FString LastResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Data")
		FString FunctionName;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Data")
	//	TArray<FParameterHUD> Inputs;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Data")
	//	TArray<FParameterHUD> Outputs;
};
