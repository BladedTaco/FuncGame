// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdLT.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdLT : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdLT();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
