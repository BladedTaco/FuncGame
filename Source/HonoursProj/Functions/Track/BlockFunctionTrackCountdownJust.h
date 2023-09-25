// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Track/BlockFunctionTrackCountdown.h"
#include "BlockFunctionTrackCountdownJust.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionTrackCountdownJust : public ABlockFunctionTrackCountdown
{
	GENERATED_BODY()
public:
	ABlockFunctionTrackCountdownJust();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
