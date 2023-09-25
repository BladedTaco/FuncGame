// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionNum.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class HONOURSPROJ_API ABlockFunctionNum : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionNum();

	virtual void SetFunctionTypes() override;

	// virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
