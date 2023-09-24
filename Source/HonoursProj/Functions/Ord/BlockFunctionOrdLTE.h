// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionOrd.h"

#include "BlockFunctionOrdLTE.generated.h"

UCLASS()
class HONOURSPROJ_API ABlockFunctionOrdLTE : public ABlockFunctionOrd
{
	GENERATED_BODY()
public:
	ABlockFunctionOrdLTE();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
