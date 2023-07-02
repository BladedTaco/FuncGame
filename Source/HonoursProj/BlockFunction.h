// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Func_gen.h"
#include "Containers/StaticArray.h"

#include "BlockFunction.generated.h"


template <typename First, typename... Rest>
class TVariant;


using ValType = TTuple<UType*, void*>;
using ValArray = TArray<ValType>;
using ValPartial = Arr<ValType, void*>;

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
class HONOURSPROJ_API ABlockFunction : public AHonoursProjBlock {
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

	TArray<void*> OutputValues;
	TArray<ValPartial> OutputPartials;


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

	// Partially/Fully Apply Inputs on InnerFunc
	ValArray GetValue();
	// Helpers
	ValPartial ApplyInput(int output, ValArray& vals, int idx, Arr<ValArray&, TArray<void*>> f);
	TVariant<void*, ValPartial> ApplyInputs(int output, ValArray& vals, int idx, Arr<ValArray&, TArray<void*>> f);

	// Interaction Handlers
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;


	UFUNCTION()
		UType* ResolveType();
	ValArray CollectInputs();

	// The Implementation of a Function
	virtual Arr<ValArray&, TArray<void*>> GetInnerFunc() PURE_VIRTUAL(ABlockFunction::GetInnerFunc,
		return { [](ValArray& x) -> TArray<void*> { return {}; } };
	);

};