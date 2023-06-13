// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "BlockFunction.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunction : public AHonoursProjBlock
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TArray<FFuncConnector> FunctionInputs;

	UPROPERTY(EditAnywhere)
	TArray<FFuncConnector> FunctionOutputs;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleRClick(UPrimitiveComponent* ClickedComponent) override;
};
