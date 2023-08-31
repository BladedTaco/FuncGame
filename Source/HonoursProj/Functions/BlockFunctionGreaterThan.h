// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionGreaterThan.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionGreaterThan : public ABlockFunction
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
		bool ConcreteOutputs;

public:
	ABlockFunctionGreaterThan();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
