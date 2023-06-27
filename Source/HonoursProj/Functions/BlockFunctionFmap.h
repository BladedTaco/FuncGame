// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionPull.h"

#include "Types/Types_gen.h"

#include "BlockFunctionFmap.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionFmap : public ABlockFunctionPull
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	FFunctionInfo BaseType;

	UPROPERTY(VisibleAnywhere)
	FFunctionInfo CurrentType;


	ABlockFunctionFmap();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void* GetValue() override;

	FFunctionInfo ResolveType();

};
