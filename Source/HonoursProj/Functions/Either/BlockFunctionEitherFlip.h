// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "Types/Dataclass/Either_gen.h"

#include "BlockFunctionEitherFlip.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionEitherFlip : public ABlockFunction
{
	GENERATED_BODY()

public:
	ABlockFunctionEitherFlip();
public:
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
