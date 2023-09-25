// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionNum.h"

#include "BlockFunctionNumTimes.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionNumTimes : public ABlockFunctionNum
{
	GENERATED_BODY()
public:
	ABlockFunctionNumTimes();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
