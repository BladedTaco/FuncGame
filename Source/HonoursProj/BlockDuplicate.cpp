// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockDuplicate.h"
#include "Engine/World.h"

AHonoursProjBlock* ABlockDuplicate::HandleClick(UPrimitiveComponent* ClickedComponent) {
	// Spawn new Block
	FVector myLoc = GetActorLocation();
	FRotator myRot = GetActorRotation();
	AHonoursProjBlock* newBlock = Cast<AHonoursProjBlock>(GetWorld()->SpawnActor(BlockClass, &myLoc, &myRot));
	if (newBlock) {
		// Dispatch its Click Event
		newBlock->HandleClick(NULL);
		return newBlock;
	}
	return NULL;
}

AHonoursProjBlock* ABlockDuplicate::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	return AHonoursProjBlock::HandleClick(ClickedComponent);
}