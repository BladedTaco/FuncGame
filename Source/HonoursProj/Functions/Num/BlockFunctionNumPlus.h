// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionNum.h"

#include "BlockFunctionNumPlus.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionNumPlus : public ABlockFunctionNum
{
	GENERATED_BODY()
public:
	ABlockFunctionNumPlus();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
