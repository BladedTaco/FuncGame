// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionOutput.h"
#include "FunctionInput.h"
#include "Components/StaticMeshComponent.h"

AHonoursProjBlock* AFunctionOutput::HandleClick(UPrimitiveComponent* ClickedComponent) {
	// losing active
	if (bIsActive) {
		// Hide connection mesh
		ConnectMesh->SetVisibility(false);

		// Get other, and make them handle the click
		if (auto other = Cast<AFunctionInput>(ClickedComponent->GetOwner())) {
			// Set Active
			other->bIsActive = true;
			// Handle Click
			other->HandleClick(GetBlockMesh());
		}
	}
	// Handle gaining active
	return AFunctionConnector::HandleClick(ClickedComponent);
}

AHonoursProjBlock* AFunctionOutput::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	// Break all inputs connected to this output
	for (auto inputBlock : connectedTo) {
		inputBlock->HandleRClick(ClickedComponent);
	}
	connectedTo.Empty();
	return this;
}

void AFunctionOutput::EndPlay(const EEndPlayReason::Type EndPlayReason) {	
	// Remove Connected to if it exists
	for (auto inputBlock : connectedTo) {
		if (IsValid(inputBlock)) {
			inputBlock->HandleRClick(NULL);
		}
	}
	connectedTo.Empty();
}
