// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRunBlock.h"
#include "Level/PuzzleLevelActor.h"


ATestRunBlock::ATestRunBlock() {
	// Create and Position TextComponent
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RunText"));
	TextComponent->SetRelativeLocation(FVector::UpVector * 100);
	TextComponent->SetWorldRotation(FRotator(90, 0, 180));
	TextComponent->SetRelativeScale3D(FVector(5));
	TextComponent->SetupAttachment(RootComponent);

	// Set Up Text Component Text
	TextComponent->SetText(FText::FromString(FString(TEXT("Start\nLevel"))));
	TextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	TextComponent->SetHorizontalAlignment(EHTA_Center);
}

AHonoursProjBlock* ATestRunBlock::HandleClick(UPrimitiveComponent* ClickedComponent) {

	if (!IsValid(PuzzleActor)) {
		TextComponent->SetText(FString("Bad\nActor"));
		return NULL;
	}

	// Update Text
	TextComponent->SetText(FText::FromString(FString(TEXT("Run\nTest"))));

	PuzzleActor->RunTest();

	// Return no Block
	return NULL;
}

AHonoursProjBlock* ATestRunBlock::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	// Ignore
	return NULL;
}