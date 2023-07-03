// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionInput.h"
#include "FunctionOutput.h"
#include "Components/StaticMeshComponent.h"

void AFunctionInput::Tick(float DeltaSeconds) {
	if (connectedTo) {
		FVector me = GetBlockMesh()->GetComponentLocation();
		FVector target = connectedTo->GetBlockMesh()->GetComponentLocation();
		me.Z = target.Z = ConnectMesh->GetComponentLocation().Z;
		ConnectMesh->SetWorldTransform(Connect(me, target));
	} else {
		AFunctionConnector::Tick(DeltaSeconds);
	}
}

AHonoursProjBlock* AFunctionInput::HandleClick(UPrimitiveComponent* ClickedComponent) {
	// Remove any existing Connections
	HandleRClick(ClickedComponent);

	// losing active
	if (bIsActive) {
		// Give Connection
		if (auto other = Cast<AFunctionOutput>(ClickedComponent->GetOwner())) {
			if (GetAttachParentActor() != other->GetAttachParentActor()) {
				
				UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));

				// Connect input to output
				connectedTo = other;
				ConnectMesh->SetVisibility(true); 

				// Connect Output back
				if (!other->connectedTo.Contains(this)) {
					other->connectedTo.Add(this);
				}
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("NO OVERLAP"));
			ConnectMesh->SetVisibility(false);
		}
	}
	// Handle gaining active
	return AFunctionConnector::HandleClick(ClickedComponent);
}

AHonoursProjBlock* AFunctionInput::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	// Remove Connected to if it exists
	if (connectedTo) {
		connectedTo->connectedTo.Remove(this);
		connectedTo = NULL;
	}
	// Make ConnectMesh Invisible
	ConnectMesh->SetVisibility(false);
	// Return self
	return this;
}

void AFunctionInput::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	// Remove Connected to if it exists
	if (connectedTo && IsValid(connectedTo)) {
		connectedTo->connectedTo.Remove(this);
		connectedTo = NULL;
	}
}

UType* AFunctionInput::ResolveType() {
	if (connectedTo && IsValid(connectedTo)) {
		return connectedTo->ResolveType();
	}
	return ParameterInfo.Type;
}

ValType AFunctionInput::GetValue() {	
	UType* type = ResolveType();
	// Handle no connection
	if (!connectedTo) { return MakeTuple(type, ( void* )NULL);  }

	// Return value from connection
	return connectedTo->GetValue();
}
