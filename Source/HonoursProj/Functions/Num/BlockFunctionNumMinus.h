// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionNum.h"

#include "BlockFunctionNumMinus.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionNumMinus : public ABlockFunctionNum
{
	GENERATED_BODY()
public:
	ABlockFunctionNumMinus();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
