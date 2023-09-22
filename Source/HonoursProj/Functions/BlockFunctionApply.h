// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionApply.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionApply : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionApply();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
