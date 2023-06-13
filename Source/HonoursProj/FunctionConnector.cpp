// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionConnector.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"


// Sets default values
AFunctionConnector::AFunctionConnector() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial")) {}
	};
	static FConstructorStatics ConstructorStatics;


	// Create static mesh component
	auto BlockMesh = GetBlockMesh();
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.1f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());

	//RootComponent = BlockMesh;

}

void AFunctionConnector::HandleClick(UPrimitiveComponent* ClickedComponent) {
	bIsActive = !bIsActive;
	if (bIsActive) {
		clickOffset = MousePos() - GetActorLocation();
		// Change material
		GetBlockMesh()->SetMaterial(0, OrangeMaterial);
	} else {
		// Create Connections
		TArray<AActor*> overlaps;
		GetOverlappingActors(overlaps, AFunctionConnector::StaticClass());

		// Sort Candidate Connections so that closest is first
		overlaps.Sort([this](const AActor& a, const AActor& b) {
			return a.GetDistanceTo(this) < b.GetDistanceTo(this);
		});

		// Give Connection
		if (overlaps.IsValidIndex(0)) {
			connectedTo = Cast<AFunctionConnector>(overlaps[0]);
		}

		// Change material
		GetBlockMesh()->SetMaterial(0, BaseMaterial);
	}
}

void AFunctionConnector::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	connectedTo = NULL;
}
