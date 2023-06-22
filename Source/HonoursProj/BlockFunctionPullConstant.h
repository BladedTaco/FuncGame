// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionPull.h"

#include "Types/Int.gen.h"

#include "BlockFunctionPullConstant.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionPullConstant : public ABlockFunctionPull
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int value = 0;

	Number<int> numValue = Number<int>(value);

	virtual void* GetValue() override;
};
