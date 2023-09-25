// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionNum.h"

#include "BlockFunctionNumSign.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionNumSign : public ABlockFunctionNum
{
	GENERATED_BODY()
public:
	ABlockFunctionNumSign();

	virtual void SetFunctionTypes() override;

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
