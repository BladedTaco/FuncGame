// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdGTE.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdGTE : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdGTE();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
