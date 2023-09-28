// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionMaybe.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionMaybe : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionMaybe();
public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};