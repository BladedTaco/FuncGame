// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdMaxMaybe.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdMaxMaybe : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdMaxMaybe();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
