// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EditorUserWidget.h"

#include "ParameterHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class HONOURSPROJ_API UParameterHUD : public UEditorUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Data")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Data")
		FString Type;
};
