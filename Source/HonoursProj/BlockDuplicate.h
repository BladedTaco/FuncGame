// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"
#include "BlockDuplicate.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockDuplicate : public AHonoursProjBlock
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHonoursProjBlock> BlockClass;

	virtual void HandleClick(UPrimitiveComponent* ClickedComponent) override;
};
