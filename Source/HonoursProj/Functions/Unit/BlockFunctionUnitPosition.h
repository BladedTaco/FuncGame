// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"
#include "BlockFunctionUnitPosition.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionUnitPosition : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
