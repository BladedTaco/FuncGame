// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionFoldR.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionFoldR : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionFoldR();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
