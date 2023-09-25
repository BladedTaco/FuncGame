// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionEitherRightFrom.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionEitherRightFrom : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionEitherRightFrom();
public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
