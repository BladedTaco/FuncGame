// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "Boss.generated.h"


UCLASS(Blueprintable, BlueprintType, Abstract)
class HONOURSPROJ_API ABoss : public AUnit
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// Level Sequence Control
	UFUNCTION(BlueprintCallable, Category = "Level Sequence")
	bool Attack();
};
