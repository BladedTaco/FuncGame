// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionOutput.h"
#include "FunctionInput.h"
#include "BlockFunction.h"
#include "Components/StaticMeshComponent.h"

AHonoursProjBlock* AFunctionOutput::HandleClick(UPrimitiveComponent* ClickedComponent) {
	// Proprogate
	Function->Propagate({ EPropagable::DIRTY });
	// losing active
	if (bIsActive) {
		// Hide connection mesh
		ConnectMesh->SetVisibility(false);

		// Get other, and make them handle the click
		if (auto other = Cast<AFunctionInput>(ClickedComponent->GetOwner())) {
			if (ValidConnections.Contains(other)) {
				// Set Active
				other->bIsActive = true;
				// Handle Click
				other->HandleClick(GetBlockMesh());
			}
		}
	}
	// Handle gaining active
	return AFunctionConnector::HandleClick(ClickedComponent);
}

AHonoursProjBlock* AFunctionOutput::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	auto copy = connectedTo;
	// Proprogate
	Function->Propagate({ EPropagable::DIRTY });
	// Break all inputs connected to this output
	for (auto inputBlock : copy) {
		inputBlock->HandleRClick(ClickedComponent);
	}
	connectedTo.Empty();
	return this;
}

void AFunctionOutput::EndPlay(const EEndPlayReason::Type EndPlayReason) {	
	// Remove Connected to if it exists
	auto copy = connectedTo;
	for (auto inputBlock : copy) {
		if (IsValid(inputBlock)) {
			inputBlock->HandleRClick(NULL);
		}
	}
	connectedTo.Empty();
}

UType* AFunctionOutput::ResolveType() {
	TMap<UType*, UType*> ptrMap = {};
	// Copy Owners OutputArrow
	UType* arrow = Function->ResolveType()->DeepCopy(ptrMap);
	// Get a pointer to the arrow
	UTypePtr* arrowPtr = UTypePtr::New(arrow);

	// Move down the arrow until a TypeVar is found
	while (arrowPtr && arrowPtr->Valid() && !arrowPtr->Get()->IsA<UTypeVar>()) {
		arrowPtr = Cast<UTypePtr>(arrowPtr->GetTemplates()[1]);
	}
	// Apply the Outputs Type to the TypeVar
	//Cast<UTypeVar>(arrowPtr->Get())->ApplyEvidence(ParameterInfo.Type);
	Cast<UTypeVar>(arrowPtr->Get())->ApplyEvidence(Function->Outputs[Index].Type->DeepCopy(ptrMap));

	// Return the arrow with applied type
	return arrow;
}

VStar AFunctionOutput::GetValue() {
	return std::move(Function->GetValue()[Index]);
}
