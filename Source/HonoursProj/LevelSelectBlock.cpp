// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSelectBlock.h"
#include "Kismet/GameplayStatics.h"

ALevelSelectBlock::ALevelSelectBlock()
{
	// Create and Position TextComponent
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LevelText"));
	TextComponent->SetRelativeLocation(FVector::UpVector * 100);
	TextComponent->SetWorldRotation(FRotator(90, 0, 180));
	TextComponent->SetRelativeScale3D(FVector(5));
	TextComponent->SetupAttachment(RootComponent);

	// Set Up Text Component Text
	TextComponent->SetText(FText::FromString(FString(TEXT("?"))));
	TextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	TextComponent->SetHorizontalAlignment(EHTA_Center);
}

AHonoursProjBlock* ALevelSelectBlock::HandleClick(UPrimitiveComponent* ClickedComponent)
{
	// Move to Level
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);

	// Return no Block
	return NULL;
}

AHonoursProjBlock* ALevelSelectBlock::HandleRClick(UPrimitiveComponent* ClickedComponent)
{
	// Ignore
	return NULL;
}
