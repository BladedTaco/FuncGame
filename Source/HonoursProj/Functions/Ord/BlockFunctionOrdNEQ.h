// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdNEQ.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdNEQ : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdNEQ();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
