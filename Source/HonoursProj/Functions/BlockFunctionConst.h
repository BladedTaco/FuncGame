// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionConst.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionConst : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionConst();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
