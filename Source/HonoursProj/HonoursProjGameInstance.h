// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Utils/ColourGroup.h"

#include "HonoursProjGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API UHonoursProjGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Accessor for C++ & BP. Should be self-explanatory
	UFUNCTION(
		BlueprintPure,
		Category = "Persistence",
		meta = (
			DisplayName = "Get TypeVar Colour Group",
			Keywords = "TypeVarColourGroup")
	)
	UColourGroup* TypeVarColourGroup();


protected:
	// Clean Up Singletons
	virtual void Shutdown() override;

private:
	// Singleton Pointer
	UPROPERTY(VisibleAnywhere, Transient)
	UColourGroup* TypeVarColourGroupInstance;
};
