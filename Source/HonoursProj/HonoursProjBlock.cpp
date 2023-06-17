// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonoursProjBlock.h"
#include "HonoursProjBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

#include "HonoursProjPlayerController.h"
#include "Kismet/GameplayStatics.h"

AHonoursProjBlock::AHonoursProjBlock() {
	// Structure to hold one-time initialization
	struct FConstructorStatics {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> LitMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> UnlitMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ActiveMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, LitMaterial(TEXT("/Game/Puzzle/Meshes/WhiteMaterial.WhiteMaterial"))
			, UnlitMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, ActiveMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial")) {}
	}; 
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.UnlitMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);

	// Save a pointer to the orange material
	LitMaterial = ConstructorStatics.LitMaterial.Get();
	UnlitMaterial = ConstructorStatics.UnlitMaterial.Get();
	ActiveMaterial = ConstructorStatics.ActiveMaterial.Get();

	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}


FVector AHonoursProjBlock::MousePos() {
	FVector worldPos, worldDir;
	auto playerCon = GetWorld()->GetFirstPlayerController<AHonoursProjPlayerController>();
	playerCon->DeprojectMousePositionToWorld(worldPos, worldDir);
	return worldPos;
}

void AHonoursProjBlock::Tick(float DeltaSeconds) {
	if (bIsActive) {
		SetActorLocation(MousePos() - clickOffset);
	}
}


AHonoursProjBlock* AHonoursProjBlock::HandleClick(UPrimitiveComponent* ClickedComponent) {
	bIsActive = !bIsActive;
	if (bIsActive) {
		clickOffset = MousePos() - GetActorLocation();
		// Change material
		BlockMesh->SetMaterial(0, ActiveMaterial);
	} else {
		// Change material
		BlockMesh->SetMaterial(0, UnlitMaterial);
	}
	return this;
}

AHonoursProjBlock* AHonoursProjBlock::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	if (ClickedComponent == BlockMesh) {
		Destroy();
		return NULL;
	}
	return this;
}


void AHonoursProjBlock::Highlight(bool bOn) {
	// Do not highlight if the block has already been activated.
	if (bIsActive) {
		return;
	}

	if (bOn) {
		BlockMesh->SetMaterial(0, LitMaterial);
	} else {
		BlockMesh->SetMaterial(0, UnlitMaterial);
	}
}
