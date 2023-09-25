// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"
#include "BlockFunctionUnitPositionMoveLR.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionUnitPositionMoveLR : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:
	ABlockFunctionUnitPositionMoveLR();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
