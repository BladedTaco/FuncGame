// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdMax.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdMax : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdMax();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
