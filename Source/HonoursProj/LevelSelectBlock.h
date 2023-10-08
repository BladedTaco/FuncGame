// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"
#include "Components/TextRenderComponent.h"
#include "LevelSelectBlock.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ALevelSelectBlock : public AHonoursProjBlock
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* TextComponent;

public:
	ALevelSelectBlock();

	// Level
	UPROPERTY(EditAnywhere)
	FName LevelName;

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;
};
