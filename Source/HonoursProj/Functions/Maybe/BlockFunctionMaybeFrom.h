// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionMaybeFrom.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionMaybeFrom : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionMaybeFrom();
public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
