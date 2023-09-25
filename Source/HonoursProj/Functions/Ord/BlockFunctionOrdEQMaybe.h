// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdEQMaybe.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdEQMaybe : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdEQMaybe();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
