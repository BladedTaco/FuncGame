// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Functions/Track/BlockFunctionTrack.h"
#include "BlockFunctionTrackCountdown.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionTrackCountdown : public ABlockFunctionTrack
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp)
	float Countdown = 99.0f;

	ABlockFunctionTrackCountdown();

	virtual void SetFunctionTypes() override;
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
};
