// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Func_gen.h"


#include "Types/VStar.h"
#include "Utils/MaskedBitFlags.h"

#include "HUD/AutoScalingHUD.h"

#include "HUD/FunctionHUD.h"

#include "BlockFunction.generated.h"

USTRUCT(BlueprintType)
struct FParameter {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
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

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPropagable : uint8 {
	NONE		= 0				UMETA(Hidden),
	DIRTY		= 1 << 0,
	VALID		= 1 << 1,
	GETVALUE	= 1 << 2,
	ALL			= ((1 << 3) - 1)	UMETA(Hidden)
};
ENUM_CLASS_FLAGS(EPropagable);

/**
 * 
 */
UCLASS(Abstract)
class HONOURSPROJ_API ABlockFunction : public AHonoursProjBlock {
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Functions")
		void SpawnConnectors();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Functions")
		void SpawnAllConnectors();



private:
	UPROPERTY(VisibleAnywhere)
		EPropagable Status = EPropagable::ALL;

public:

	virtual bool ShouldTickIfViewportsOnly() const override { return true; }


	// Status Handling
	void Propagate(MaskedBitFlags<EPropagable> Values, bool Origin = true);
	void PropagateToEnds(MaskedBitFlags<EPropagable> Values);

	inline bool IsStatus(EPropagable InTest) const { return EnumHasAllFlags(Status, InTest); }

	// Materials
	UPROPERTY(EditAnywhere, Category = BlockMaterials)
		UMaterialInstance* ErrorMaterial;

	// Type Resolution
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Inputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Outputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		UType* OutputArrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UTypeVar*> TypeVars;


	// Parameter Actors
	UPROPERTY(VisibleAnywhere)
		TArray<class AFunctionInput*> InputBlocks;
	UPROPERTY(VisibleAnywhere)
		TArray<class AFunctionOutput*> OutputBlocks;

	// Block HUD
	THUD<UFunctionHUD> HUD;

	UPROPERTY(VisibleAnywhere)
		FString FunctionName;
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	ABlockFunction();

	// Partially/Fully Apply Inputs on InnerFunc
	VStarArrayReturn GetValue();
	// Helpers
	Arr<VStar, VStar> ApplyInput(int output, TArray<VStar> vals, int idx, Arr<VStarArray, VStarArrayReturn> f);
	VStar ApplyInputs(int output, TArray<VStar> vals, int idx, Arr<VStarArray, VStarArrayReturn> f);

	UType* ResolveTypesWithPartial(int output, const TArray<VStar>& partialInputs);

	// Interaction Handlers
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;


	UFUNCTION()
		UType* ResolveType();
	VStarArrayReturn CollectInputs();

	// The Implementation of a Function
	virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() PURE_VIRTUAL(ABlockFunction::GetInnerFunc,
		return { [](VStarArray x) -> VStarArrayReturn { return {}; } };
	);
	// The Type Declaration of a Function
	virtual void SetFunctionTypes() PURE_VIRTUAL(ABlockFunction::SetFunctionTypes, return;);
};