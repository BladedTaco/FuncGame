// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionCall.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionCall : public ABlockFunction
{
	GENERATED_BODY()

public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
