// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceDirector.h"
#include "PuzzleLevelSequenceDirector.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API UPuzzleLevelSequenceDirector : public ULevelSequenceDirector
{
	GENERATED_BODY()

public:
	// Utility Functions
	UFUNCTION(BlueprintCallable, Category = "Level Sequence")
	void ReplaceActor(AActor* Replace, const TArray<AActor*>& With);
};
