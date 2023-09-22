// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdMin.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdMin : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdMin();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
