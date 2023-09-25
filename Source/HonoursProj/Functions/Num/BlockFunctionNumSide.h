// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionNum.h"

#include "BlockFunctionNumSide.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionNumSide : public ABlockFunctionNum
{
	GENERATED_BODY()
public:
	ABlockFunctionNumSide();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
