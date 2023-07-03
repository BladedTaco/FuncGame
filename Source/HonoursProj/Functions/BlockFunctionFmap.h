// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "BlockFunctionFmap.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionFmap : public ABlockFunction
{
	GENERATED_BODY()
public:
	virtual void SetFunctionTypes() override;

	virtual Arr<ValArray&, TArray<void*>> GetInnerFunc() override;
};
