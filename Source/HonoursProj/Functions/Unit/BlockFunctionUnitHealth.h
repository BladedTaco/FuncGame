// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"
#include "BlockFunctionUnitHealth.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionUnitHealth : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:
	ABlockFunctionUnitHealth();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
