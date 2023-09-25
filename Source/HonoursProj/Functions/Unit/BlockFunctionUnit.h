// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "Level/Unit.h"

#include "AssetLoader_gen.h"

#include "BlockFunctionUnit.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HONOURSPROJ_API ABlockFunctionUnit : public ABlockFunction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	AUnit* Unit;

	//virtual void SetFunctionTypes() override;
	//virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
