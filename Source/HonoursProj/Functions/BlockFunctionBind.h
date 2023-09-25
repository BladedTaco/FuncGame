// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionBind.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionBind : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionBind();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
