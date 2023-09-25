// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Unit/Skills/BlockFunctionSkill.h"
#include "BlockFunctionSkillBlockEither.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionSkillBlockEither : public ABlockFunctionSkill
{
	GENERATED_BODY()
public:
	ABlockFunctionSkillBlockEither();


	UPROPERTY(EditAnywhere)
	AUnit* Shield;

	UPROPERTY(EditAnywhere)
	FVector2D ShieldFacing;

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
