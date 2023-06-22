// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"

#include "Functional/Prelude.h"

#include "BlockFunctionPull.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionPull : public ABlockFunction
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	class UTextRenderComponent* TextComponent;

	ABlockFunctionPull();
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;

	//Function<void*, void*> InnerFunction = [](auto& a) { return a; };

	virtual void* GetValue() { return ( void* )0; };
};
