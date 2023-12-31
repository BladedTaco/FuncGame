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
		ConnectMesh->SetVisibility(true);
		ConnectMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	} 
	AFunctionConnector::Tick(DeltaSeconds);
}

AHonoursProjBlock* AFunctionInput::HandleClick(UPrimitiveComponent* ClickedComponent) {
	// Proprogate
	Function->Propagate({ EPropagable::DIRTY });
	// Remove any existing Connections
	HandleRClick(ClickedComponent);

	// losing active
	if (bIsActive) {
		// Give Connection
		if (auto other = Cast<AFunctionOutput>(ClickedComponent->GetOwner())) {
			//UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));

			// Connect input to output
			connectedTo = other;
			ConnectMesh->SetVisibility(true);
			ConnectMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

			// Connect Output back
			if (!other->GetConnectedInputs().Contains(this)) {
				other->connectedTo.Add(this);
			}
		} else {
			//UE_LOG(LogTemp, Warning, TEXT("NO OVERLAP"));
			ConnectMesh->SetVisibility(false);
			ConnectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	// Handle gaining active
	return AFunctionConnector::HandleClick(ClickedComponent);
}

AHonoursProjBlock* AFunctionInput::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	// Proprogate
	Function->Propagate({ EPropagable::DIRTY });
	// Remove Connected to if it exists
	if (connectedTo) {
		connectedTo->connectedTo.Remove(this);
		connectedTo = NULL;
	}
	if (IsValid(ConnectMesh)) {
	// Make ConnectMesh Invisible
		ConnectMesh->SetVisibility(false);
		ConnectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	// Return self
	return this;
}

void AFunctionInput::BeginPlay() {
	Super::BeginPlay();

	// Make ConnectMesh Raycast Detectable
	ConnectMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AFunctionInput::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	// Remove Connected to if it exists
	if (connectedTo && IsValid(connectedTo)) {
		connectedTo->connectedTo.Remove(this);
		connectedTo = NULL;
	}
}

UType* AFunctionInput::ResolveType_Impl() {
	if (connectedTo && IsValid(connectedTo)) {
		// TODO, this affects ParameterInfo
		return connectedTo->ResolveType();
	}
	return ParameterInfo.Type;
}

const TArray<AFunctionConnector*> AFunctionInput::GetConnections() {
	return (TArray<AFunctionConnector*>)GetConnectedOutputs();
}

const TArray<AFunctionOutput*> AFunctionInput::GetConnectedOutputs() {
	// Return connectedTo when Valid
	if (IsValid(connectedTo)) return { connectedTo };
	// Return Nothing
	return {};
}

VStar AFunctionInput::GetValue_Impl() {
	//UType* type = ResolveType();
	// Handle no connection
	//if (!connectedTo) return VStar(ResolveType());
	if (!connectedTo) return VStar();

	// Return value from connection
	return connectedTo->GetValue();
}
