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

#include "HUD/FunctionHUD.h"
#include "HUD/ParameterHUD.h"

#include "AssetLoader_gen.h"

#include "Algo/AllOf.h"
#include "Algo/Partition.h"

#include "MyUtils.h"

#include "HUD/AutoScalingHUD.h"

#include "Engine.h"

TArray<AFunctionConnector*> ABlockFunction::GetConnectors() {
	TArray<AFunctionConnector*> connectors;
	connectors.Append(InputBlocks);
	connectors.Append(OutputBlocks);

	// Filter Invalid Connectors
	return connectors.FilterByPredicate([](AFunctionConnector* connector) {
		return IsValid(connector);
	});
}

ABlockFunction::ABlockFunction() {
	ErrorMaterial = Assets()->Material.Red.Get();

	HUD.UpdateComponent(GetHUDComponent());
	HUD.Component->SetRelativeLocation(FVector::UpVector * 200.0f);
	HUD.Component->SetWorldRotation(FRotator(90, 0, 180));
	HUD.Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HUD.Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HUD.Component->SetDrawAtDesiredSize(true);
	HUD.Component->SetupAttachment(RootComponent);
	HUD.Component->SetWidgetClass(Assets()->HUD.Function.Class);
	//HUD.Component->RegisterComponent();

	TypeVars = {};
	Inputs = {};
	Outputs = {};

	InputBlocks = {};
	OutputBlocks = {};
}

void ABlockFunction::DestroyConnectors(AActor* deletedActor) {
	auto actor = Cast<ABlockFunction>(deletedActor);
	if (!actor) return;

	for (auto connector : actor->GetConnectors()) {
		if (IsValid(connector)) continue;
		connector->Destroy();
	}
	actor->InputBlocks = {};
	actor->OutputBlocks = {};
	
}

void ABlockFunction::OnConstruction(const FTransform& Transform) {
	GEngine->OnLevelActorDeleted().AddUObject(this, &ABlockFunction::DestroyConnectors);

	Super::OnConstruction(Transform);
	/*HUD.Component->InitWidget();
	HUD.Component->UpdateWidget();*/
	HUD.UpdateComponent(GetHUDComponent());
	if (HUD.Component.IsValid()) {
		HUD.Component->SizeToBounds(GetBlockMesh());
	}

	ConnectorsSpawned = InputBlocks.Num() + OutputBlocks.Num() > 0;

	for (auto connector : GetConnectors()) {
		if (connector->GetAttachParentActor() != this) {
			if (connector->GetAttachParentActor() == nullptr) {
				connector->Destroy();
			}
			ConnectorsSpawned = false;
			InputBlocks = {};
			OutputBlocks = {};
		}
	}

	SpawnConnectors();
}

void ABlockFunction::BeginDestroy() {
	for (auto connector : GetConnectors()) {
		connector->Destroy();
	}
	Super::BeginDestroy();
}

void ABlockFunction::SpawnConnectors() {
	// Requires World
	if (!GetWorld()) return;

	// Set Function Signature
	SetFunctionTypes();

	HUD.UpdateComponent(GetHUDComponent());
	HUD.Component->SizeToBounds(GetBlockMesh());

	if (!HUD.Inst().IsValid()) return;

	HUD.Instance->FunctionName = FunctionName;
	HUD.Instance->LastResult = FString(TEXT("Unevaluated"));

	Status |= EPropagable::DIRTY;

	HUD.RecompileInstanceClass();
	HUD.UpdateInEditor(Assets()->HUD.Parameter.Class);

	// Call once
	if (ConnectorsSpawned) {
		FParameter p;
		for (auto param : GetConnectors()) {
			param->Function = this;
			if (param->IsA<AFunctionInput>()) {
				p = Inputs[param->Index];
			} else {
				p = Outputs[param->Index];
			}
			param->ParameterInfo = FParameter(p.Name, UTypePtr::New(p.Type));
		}
		return;
	}
	ConnectorsSpawned = true;

	//// Set Function Signature
	//SetFunctionTypes();

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
		MakeTuple(-1, TEXT("Input"),  &Inputs,  (TArray<AFunctionConnector*>*) & InputBlocks,  AFunctionInput::StaticClass()),
		MakeTuple(1, TEXT("Output"), &Outputs, (TArray<AFunctionConnector*>*) & OutputBlocks, AFunctionOutput::StaticClass())
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
			actor->Function = this;
			actor->ParameterInfo = FParameter(param.Name, UTypePtr::New(param.Type));
			actor->Index = idx;
			blocks->Add(actor);
			// Attach to self
			//actor->AttachToActor(this, attachRules);
			actor->AttachToComponent(GetRootComponent(), attachRules);
			actor->SetActorRelativeLocation(FVector(100 * -idx + 50, yOff * 100, 0.5 * extent.Z));
			actor->SetupHUD(); 
			// Iterate index
			idx += 1;
		}
	}
}

void ABlockFunction::SpawnAllConnectors() {
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), actors);

	for (auto actor : actors) {
		auto func = Cast<ABlockFunction>(actor);
		func->SpawnConnectors();
		func->Status |= EPropagable::DIRTY;
		//actor->Tick(0.0f);
	}


}

void ABlockFunction::Propagate(MaskedBitFlags<EPropagable> Values, bool Origin) {
	// Dont propogate if (not the Origin) and (already satisfying Values).
	if (!Origin && Values.Satisfies(Status)) return;

	// Update Status
	Status = Values.Apply(Status);

	// Propogate
	for (auto block : OutputBlocks) {
		for (auto to : block->connectedTo) {
			to->Function->Propagate(Values, false);
		}
	}
}

void ABlockFunction::PropagateToEnds(MaskedBitFlags<EPropagable> Values) {
	// If all Outputs are Unconnected
	if (Algo::AllOf(OutputBlocks, [](const AFunctionOutput* output) {
		return output->connectedTo.Num() == 0;

	// Update Status
	})) {
		Status = Values.Apply(Status);

	// Propogate
	} else {
		for (auto block : OutputBlocks) {
			for (auto to : block->connectedTo) {
				to->Function->PropagateToEnds(Values);
			}
		}
	}
}

// Called when the game starts or when spawned
void ABlockFunction::BeginPlay() {
	Super::BeginPlay();

	HUD.UpdateComponent(GetHUDComponent());

	SpawnConnectors();
	
}

void ABlockFunction::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Tick"));

	// If Needs to update Type
	if (IsStatus(EPropagable::DIRTY)) {
		ResolveType();


		// Is Valid
		if (IsStatus(EPropagable::VALID)) {
			if (GetBlockMesh()->GetMaterial(0) == ErrorMaterial) {
				GetBlockMesh()->SetMaterial(0, UnlitMaterial);
			}
		// When Invalid
		} else {
			// Set Block to Error Material
			GetBlockMesh()->SetMaterial(0, ErrorMaterial);
		}

		//// Aggregate Validity
		//Valid = true;

		// For inputs
		for (auto input : InputBlocks) {
			//if (input->connectedTo) {
			//	input->HUD.Instance->Type = input->ResolveType()->ToString();
			//} else {
			//	input->HUD.Instance->Type = Inputs[input->Index].Type->ToString();
			//}

			input->HUD.Inst()->Type = input->ParameterInfo.Type->ToString();

			//Valid &= Inputs[input->Index].Type->Supercedes(input->ParameterInfo.Type);
			//input->HUD.Instance->Type = Inputs[input->Index].Type->ToString();
		}
		// For Outputs
		for (auto output : OutputBlocks) {
			//output->HUD.Instance->Type = output->ResolveType()->ToString();
			output->HUD.Inst()->Type = Outputs[output->Index].Type->ToString();
		}



		// Clean
		Status ^= EPropagable::DIRTY;
	}

	// If needs to update value
	if (IsStatus(EPropagable::GETVALUE)) {
		// Get Value
		GetValue();
		// Remove from Status
		Status ^= EPropagable::GETVALUE;
	}
}

// Calculate Values
AHonoursProjBlock* ABlockFunction::HandleClick(UPrimitiveComponent* ClickedComponent) {
	GetValue();
	HUD.Component->UpdateWidget();
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
		ptrMap.Add(var, var->RecursiveCopy());
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

	// Reset All TypeVars
	for (auto& typevar : TypeVars) {
		if (!typevar) return NULL;
		typevar->ResetEvidence();
	}

	// Apply Evidence

	bool Valid = true; // Aggregate Validity
	// For Each Input (reversed)
	for (int idx = InputBlocks.Num(); idx --> 0;) {
		AFunctionInput* input = InputBlocks[idx];

		// Apply Evidence When Possible
		if (input->connectedTo) {
			// Resolve Type First to check validity
			Valid 
				&= input->connectedTo->Function->IsStatus(EPropagable::VALID)
				&& Inputs[idx].Type->UnifyWith(input->ResolveType());
		}
	}

	// Update Status on Valid
	if (Valid) {
		Status |= EPropagable::VALID;
	// Propagate on invalid
	} else {
		Propagate({ EPropagable::VALID, EPropagable::NONE });
	}

	// Apply Arrow Parameters

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
ArrV ABlockFunction::ApplyInput(int output, TArray<VStar> vals, int idx, Arr<VStarArray, VStarArrayReturn> f) {
	return ArrV([this, idx, output, vals, f] (VStar val) -> VStar {
		// Copy Vals
		TArray<VStar> m_vals = vals;
		if (m_vals.IsValidIndex(idx)) {
			// Set Value
			m_vals[idx].Replace(val);
		} else {
			m_vals.Add(val);
		}

		// Recurse further
		return this->ApplyInputs(output, m_vals, idx + 1, f);
	});
};

// Partially Applies function appropriately
VStar ABlockFunction::ApplyInputs(int output, TArray<VStar> vals, int idx, Arr<VStarArray, VStarArrayReturn> f) {
	// Fully Applied Base Case
	if (!vals.IsValidIndex(idx)) {
		//TArray<VStar> f_res = f(std::move(vals));
		TArray<VStar> f_res = std::move(f(vals));
		VStar f_out = f_res[output];
		return f_out;
		//return f(vals)[output];
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
	// On Invalid, cancel
	if (!IsStatus(EPropagable::VALID)) {
		return {};
	}

	// Collect Output Types and Values
	VStarArray outputs = {};
	for (const auto& output : OutputBlocks) {
		// Either Collect Further Inputs, or Output Value
		outputs.Add(ApplyInputs(output->Index, CollectInputs(), 0, GetInnerFunc()));
	}

	// Return collected outputs
	return std::move(outputs);
}
