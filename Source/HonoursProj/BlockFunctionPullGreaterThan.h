// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionPull.h"
#include "BlockFunctionPullGreaterThan.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionPullGreaterThan : public ABlockFunctionPull
{
	GENERATED_BODY()

public:

	virtual void* GetValue() override;
	
};
