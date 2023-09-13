// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"
#include "EdgeBlockFunction.generated.h"

class ATextRenderActor;

/**
 * 
 */
UCLASS(Abstract)
class HONOURSPROJ_API AEdgeBlockFunction : public ABlockFunction
{
	GENERATED_BODY()
public:
	AEdgeBlockFunction();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	ATextRenderActor* DescriptionActor;

	UPROPERTY(EditAnywhere)
	ULocationBoundsComponent* EdgeBound;
	
};
