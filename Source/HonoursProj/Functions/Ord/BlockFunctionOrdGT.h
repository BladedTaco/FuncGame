// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdGT.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdGT : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdGT();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
