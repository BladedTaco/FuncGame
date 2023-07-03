// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunction.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Misc/TVariant.h"

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

	SetFunctionTypes();

	// Initialize Output Partials
	for (auto output : Outputs) {
		for (auto input : Inputs) {
			OutputPartials.Add(ValPartial([](ValType x) { return ( void* )NULL; }));
		}
	}

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

// Resolve Type Signature
UType* ABlockFunction::ResolveType() {
	// Intiialize Output Arrow Terminal TypeVar
	UType* outArrow = UTypeVar::New(ETypeClass::ANY);

	// For Each Input
	for (AFunctionInput* input : InputBlocks) {
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

ValArray ABlockFunction::CollectInputs() {
	ValArray out = {};

	// For Each Input
	for (AFunctionInput* input : InputBlocks) {
		// Resolve Type and Get Value
		out.Add(input->GetValue());
	}

	return out;
}


// Requests a single input, and recurses
ValPartial ABlockFunction::ApplyInput(int output, ValArray& vals, int idx, Arr<ValArray&, TArray<void*>> f) {
	return ValPartial([&](ValType val) -> void* {
		// Set Value
		vals[idx] = val;
		// Recurse further
		auto res = ApplyInputs(output, vals, idx + 1, f);

		// More to Apply
		if (res.IsType<ValPartial>()) {
			// Store Partial
			int out_idx = output * vals.Num() + idx;
			OutputPartials[out_idx] = res.Get<ValPartial>();
			// Return partial reference
			return ( void* )&OutputPartials[out_idx];

		// Final Application, passthrough value
		} else {
			return res.Get<void*>();
		}
	});
};

// Partially Applies function appropriately
TVariant<void*, ValPartial> ABlockFunction::ApplyInputs(int output, ValArray& vals, int idx, Arr<ValArray&, TArray<void*>> f) {
	TVariant<void*, ValPartial> outputVariant;

	// Fully Applied Base Case
	if (vals.Num() <= idx) {
		outputVariant.Set<void*>(f(vals)[output]);
		return outputVariant;
	}

	// Extract type and value
	const auto& [tn, vn] = vals[idx];

	// If no type for current Variable
	if (!tn) {
		// Request Type
		outputVariant.Set<ValPartial>(ApplyInput(output, vals, idx, f));
		return outputVariant;

	// typed
	} else {
		return ApplyInputs(output, vals, idx + 1, f);
	}
};

// Gets the Value of a function
ValArray ABlockFunction::GetValue() {
	// Collect Inputs
	ValArray inputs = CollectInputs();

	// Collect Output Types and Values
	ValArray outputs = {};
	for (const auto& output : OutputBlocks) {
		// Either Collect Further Inputs, or Output Value
		TVariant<void*, ValPartial> res = ApplyInputs(output->Index, { inputs }, 0, GetInnerFunc());

		// Add Resolved Output Type
		if (res.IsType<void*>()) {
			outputs.Add(ValType{
				output->ResolveType(),
				res.Get<void*>()
			});

		// Add Partially Applied Output Type
		} else if (res.IsType<ValPartial>()) {
			// Store Output Partial
			int out_idx = output->Index * inputs.Num();
			OutputPartials[out_idx] = res.Get<ValPartial>();

			// Add void* of partial with type to outputs
			outputs.Add(ValType {
				output->ResolveType(), 
				&OutputPartials[out_idx]
			});
		} else {
			UE_LOG(LogTemp, Warning, TEXT("BAD PARTIAL"));
		}
	}

	// Return collected outputs
	return outputs;
}
