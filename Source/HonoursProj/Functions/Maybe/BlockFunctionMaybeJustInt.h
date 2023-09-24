// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionMaybeJustInt.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionMaybeJustInt : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionMaybeJustInt();
public:
	UPROPERTY(EditAnywhere)
		int Value = -1;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
