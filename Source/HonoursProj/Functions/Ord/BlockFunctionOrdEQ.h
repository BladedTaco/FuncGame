// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdEQ.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdEQ : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdEQ();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
