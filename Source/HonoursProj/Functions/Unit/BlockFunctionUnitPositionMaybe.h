// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"
#include "BlockFunctionUnitPositionMaybe.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionUnitPositionMaybe : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:
	ABlockFunctionUnitPositionMaybe();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
