// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionEitherLeftBoolSign.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionEitherLeftBoolSign : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionEitherLeftBoolSign();
public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
