// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "Types/Dataclass/BaseTypes.h"

#include "BlockFunctionBool.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionBool : public ABlockFunction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		bool Value = false;

	ABlockFunctionBool();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
