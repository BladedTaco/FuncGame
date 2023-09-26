// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"
#include "BlockFunctionUnitPositionDists.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionUnitPositionDists : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:
	ABlockFunctionUnitPositionDists();


	UPROPERTY(EditAnywhere)
	AUnit* RelativeTo;


	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
