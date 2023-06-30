// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "BlockFunction.generated.h"


USTRUCT(BlueprintType)
struct FParameter {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UType* Type;
public:
	// Base Constructor
	FParameter()
		: Name("Unnamed")
		, Type() {};
	// Other Constructors
	FParameter(FString name, UType* type)
		: Name(name) 
		, Type(type) {};
};


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunction : public AHonoursProjBlock
{
	GENERATED_BODY()
	
public:
	// Type Resolution
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Inputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Outputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UType* OutputArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UTypeVar*> TypeVars;


	// Parameter Actors
	UPROPERTY(VisibleAnywhere)
		TArray<class AFunctionInput*> InputBlocks;
	UPROPERTY(VisibleAnywhere)
		TArray<class AFunctionOutput*> OutputBlocks;

	// Text Component to render value
	UPROPERTY(VisibleAnywhere)
		class UTextRenderComponent* TextComponent;
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ABlockFunction();

	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;


	UFUNCTION()
		UType* ResolveType();

	virtual void* GetValue() PURE_VIRTUAL(ABlockFunction::GetValue, return NULL;);

};
