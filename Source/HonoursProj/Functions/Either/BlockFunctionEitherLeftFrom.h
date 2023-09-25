// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionEitherLeftFrom.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionEitherLeftFrom : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionEitherLeftFrom();
public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
