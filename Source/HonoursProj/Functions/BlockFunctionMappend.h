// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionMappend.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionMappend : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionMappend();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
