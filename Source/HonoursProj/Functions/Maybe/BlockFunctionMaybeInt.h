// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionMaybeInt.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionMaybeInt : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionMaybeInt();
public:
	UPROPERTY(EditAnywhere)
		int Value = 0;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
