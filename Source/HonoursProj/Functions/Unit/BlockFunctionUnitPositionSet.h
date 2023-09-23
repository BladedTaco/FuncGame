// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"
#include "BlockFunctionUnitPositionSet.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionUnitPositionSet : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:
	ABlockFunctionUnitPositionSet();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
