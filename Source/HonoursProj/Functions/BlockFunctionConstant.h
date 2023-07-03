// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "Types/Int_gen.h"

#include "BlockFunctionConstant.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionConstant : public ABlockFunction
{
	GENERATED_BODY()
private:
	Number<int> ConcreteOutputs = { 0 };

public:
	UPROPERTY(EditAnywhere)
		int Value = 0;


	virtual Arr<ValArray&, TArray<void*>> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
