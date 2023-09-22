// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionLiftA2.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionLiftA2 : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionLiftA2();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
