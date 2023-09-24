// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/Skills/BlockFunctionSkill.h"
#include "BlockFunctionSkillPositionMaybeSet.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionSkillPositionMaybeSet : public ABlockFunctionSkill
{
	GENERATED_BODY()
public:
	ABlockFunctionSkillPositionMaybeSet();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
