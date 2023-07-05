// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunction.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"
#include "FunctionConnector.h"


#include "Algo/AllOf.h"

#include "MyUtils.h"

ABlockFunction::ABlockFunction() {
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextOutput"));
	TextComponent->SetText(FString("test"));
	TextComponent->SetRelativeLocation(FVector::UpVector * 200.0f);
	TextComponent->SetWorldRotation(FRotator(90, 0, 180));
	TextComponent->SetRelativeScale3D(FVector(10));
	TextComponent->SetupAttachment(GetBlockMesh());
}


// Called when the game starts or when spawned
void ABlockFunction::BeginPlay() {
	Super::BeginPlay();

	// Set Function Signature
	SetFunctionTypes();

	// Ensure Attachment is entirely KeepRelative
	FAttachmentTransformRules attachRules = FAttachmentTransformRules(
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		false
	);

	// Get Length from block center to top
	FVector lower, upper, extent;
	GetBlockMesh()->GetLocalBounds(lower, upper);
	extent = (upper - lower) * GetBlockMesh()->GetComponentScale();


	int idx;
	FString name;
	FActorSpawnParameters spawnParams;
	// Loop over both Inputs and Outputs
	for (auto [yOff, blockType, iterable, blocks, blockClass] : {
		MakeTuple(-1, TEXT("Input"),  &Inputs,  (TArray<AFunctionConnector*>*)&InputBlocks,  AFunctionInput::StaticClass()),
		MakeTuple( 1, TEXT("Output"), &Outputs, (TArray<AFunctionConnector*>*)&OutputBlocks, AFunctionOutput::StaticClass())
	}) {
			// Reset Index
		idx = 0;
		// For each of the Inputs/Outputs
		for (FParameter& param : *iterable) {
			// Set Actor Name
			name = FString::Format(TEXT("{0}_{1}_{2}"), { GetFName().ToString(), blockType, param.Name });
			spawnParams.Name = FName(*name);
			// Spawn Actor and give data
			AFunctionConnector* actor = GetWorld()->SpawnActor<AFunctionConnector>(blockClass, spawnParams);
			actor->ParameterInfo = FParameter(param.Name, UTypePtr::New(param.Type));
			actor->Index = idx;
			blocks->Add(actor);
			// Attach to self
			actor->AttachToActor(this, attachRules);
			actor->SetActorRelativeLocation(FVector(100 * -idx + 50, yOff*100, 0.5 * extent.Z));
			// Iterate index
			idx += 1;
		}
	}
}

// Calculate Values
AHonoursProjBlock* ABlockFunction::HandleClick(UPrimitiveComponent* ClickedComponent) {
	GetValue();
	return this;
}

// Move
AHonoursProjBlock* ABlockFunction::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	return AHonoursProjBlock::HandleClick(ClickedComponent);
}


// Resolves the Type of a Function with Partially Applied Inputs
UType* ABlockFunction::ResolveTypesWithPartial(int output, const TArray<VStar>& partialInputs) {


	// DeepCopy TypeVars and use in ptrMap
	TMap<UType*, UType*> ptrMap;
	for (UTypeVar* var : TypeVars) {
		ptrMap.Add(var, var->DeepCopy());
	}

	// Get Original Output Type
	UType* outArrow = Outputs[output].Type->DeepCopy(ptrMap);

	// Resolve Partial Applications (reversed)
	for (int idx = partialInputs.Num(); idx --> 0;) {
		const VStar* input = &partialInputs[idx];
		// Try to Resolve precursors when a Connected Type
		if (!input->Valid()) {
			// On Resolution fail, Unconnected Type, Add Arrow Layer
			outArrow = UTypeConst::New(ETypeData::FUNC, { Inputs[idx].Type->DeepCopy(ptrMap), UTypePtr::New(outArrow)});
		}
	}

	return outArrow;
}

// Resolve Type Signature
UType* ABlockFunction::ResolveType() {
	// Intiialize Output Arrow Terminal TypeVar
	UType* outArrow = UTypeVar::New(ETypeClass::ANY);

	// For Each Input (reversed)
	for (int idx = InputBlocks.Num(); idx --> 0;) {
		 AFunctionInput* input = InputBlocks[idx];
		// Try to Resolve precursors when a Connected Type
		if (!input->connectedTo) {
			// On Resolution fail, Unconnected Type, Add Arrow Layer
			outArrow = UTypeConst::New(ETypeData::FUNC, { input->ParameterInfo.Type, UTypePtr::New(outArrow) });
		}
	}

	// Set OutputArrow
	OutputArrow = outArrow;
	return OutputArrow;
}

VStarArrayReturn ABlockFunction::CollectInputs() {
	VStarArray out = {};

	// For Each Input
	for (AFunctionInput* input : InputBlocks) {
		// Resolve Type and Get Value
		out.Add(input->GetValue());
	}

	return std::move(out);
}


// Requests a single input, and recurses
Arr<VStar, VStar> ABlockFunction::ApplyInput(int output, VStarArray vals, int idx, Arr<VStarArray, VStarArrayReturn> f) {
	return Arr<VStar, VStar>([&] (VStar&& val) -> VStar {
		// Copy Vals
		TArray<VStar> m_vals = vals;
		// Set Value
		m_vals[idx].Replace(val);
		// Recurse further
		return ApplyInputs(output, std::move(m_vals), idx + 1, f);
	});
};

// Partially Applies function appropriately
VStar ABlockFunction::ApplyInputs(int output, VStarArray vals, int idx, Arr<VStarArray, VStarArrayReturn> f) {
	// Fully Applied Base Case
	if (vals.Num() <= idx) {
		return std::move(f(std::move(vals))[output]);
	}

	// Extract type and value
	VStar* val = &vals[idx];

	// If no type for current Variable
	if (!val->Valid()) {
		// Request Type
		UType* retType = ResolveTypesWithPartial(output, vals);
		return VStar(retType, ApplyInput(output, std::move(vals), idx, f));
	// typed
	} else {
		return ApplyInputs(output, std::move(vals), idx + 1, f);
	}
}

// Gets the Value of a function
VStarArrayReturn ABlockFunction::GetValue() {
	// Collect Output Types and Values
	VStarArray outputs = {};
	for (const auto& output : OutputBlocks) {
		// Either Collect Further Inputs, or Output Value
		outputs.Add(ApplyInputs(output->Index, CollectInputs(), 0, GetInnerFunc()));
	}

	// Return collected outputs
	return std::move(outputs);
}
