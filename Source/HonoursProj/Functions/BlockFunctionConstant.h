// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "Types/Dataclass/BaseTypes.h"

#include "BlockFunctionConstant.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionConstant : public ABlockFunction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		int Value = 5;

	ABlockFunctionConstant();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
