// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "BlockFunctionCounter.generated.h"

/**
 *
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionCounter : public ABlockFunction {
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		float CurrentValue = 0.0f;
public:
	UPROPERTY(EditAnywhere)
		float TickRate = 2.0f;
	UPROPERTY(EditAnywhere)
		int MaxValue = 10.0f;
public:
	ABlockFunctionCounter();

	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;

	virtual void Tick(float DeltaTime) override;
};
