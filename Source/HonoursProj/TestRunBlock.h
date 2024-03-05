// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"
#include "Components/TextRenderComponent.h"
#include "TestRunBlock.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ATestRunBlock : public AHonoursProjBlock
{
	GENERATED_BODY()

	/** Text Render component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TextComponent;

public:
	ATestRunBlock();

	// Level
	UPROPERTY(EditAnywhere)
	class APuzzleLevelActor* PuzzleActor;

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;
};
