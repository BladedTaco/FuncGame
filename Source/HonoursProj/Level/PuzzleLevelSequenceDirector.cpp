// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleLevelSequenceDirector.h"

#include "GameFramework/Actor.h"

#include "BlockFunction.h"

void UPuzzleLevelSequenceDirector::ReplaceActor(AActor* Replace, const TArray<AActor*>& With) {
	
	TArray<AActor*> ValidWith = {};
	for (AActor* block : With) {
		if (IsValid(block)) {
			ValidWith.Add(block);
		}
	}

	FVector Loc = Replace->GetActorLocation();
	float AngleStep = 360 / ValidWith.Num();
	float Angle = 0;
	FVector Arm = FVector(20, 0, 0);
	for (AActor* block : ValidWith) {
		block->SetActorLocation(Loc + Arm.RotateAngleAxis(Angle, FVector::UpVector));
		Angle += AngleStep;
	}

	if (auto func = Cast<ABlockFunction>(Replace)) {
		func->Destroy();
	}
}
