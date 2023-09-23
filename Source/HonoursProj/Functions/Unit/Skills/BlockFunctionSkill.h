// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/BlockFunctionUnit.h"

#include "Level/StatusBar.h"

#include "BlockFunctionSkill.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HONOURSPROJ_API ABlockFunctionSkill : public ABlockFunctionUnit
{
	GENERATED_BODY()
public:
	ABlockFunctionSkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatusType StatusType = EStatusType::MANA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StatusCost = 10;

	// virtual void SetFunctionTypes() override;
	// virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;

protected:
	//  Try the skill, returning success / failure
	bool TrySkill() const;
};
