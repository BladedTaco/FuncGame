// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HUD/EditorUserWidget.h"
#include "TextHUD.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HONOURSPROJ_API UTextWidget : public UWidgetComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void SetText(FString NewText);


};

/**
 *
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class HONOURSPROJ_API UTextHUD : public UEditorUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Data")
	FString Text;
};
