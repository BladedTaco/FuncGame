// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionPull.h"

#include "Types/Maybe.gen.h"
#include "Types/Int.gen.h"

#include "BlockFunctionPullMaybe.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionPullMaybe : public ABlockFunctionPull
{
	GENERATED_BODY()

public:

	Maybe<int> value = Maybe<int>::Nothing();

	virtual void* GetValue() override;
};
