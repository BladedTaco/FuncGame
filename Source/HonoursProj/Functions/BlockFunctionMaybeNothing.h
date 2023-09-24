// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionMaybeNothing.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionMaybeNothing : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionMaybeNothing();
	
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
