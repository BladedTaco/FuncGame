// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonoursProjBlock.h"
#include "HonoursProjBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

#include "HUD/AutoScalingHUD.h"

#include "HonoursProjPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "MyUtils.h"

#include "AssetLoader_gen.h"
//#include "OutputDeviceNull.h"

AHonoursProjBlock::AHonoursProjBlock() {
	// Save a pointer to the materials
	LitMaterial = Assets()->Material.White.Get();
	UnlitMaterial = Assets()->Material.Blue.Get();
	ActiveMaterial = Assets()->Material.Orange.Get();

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	
	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(Assets()->Mesh.PuzzleCube.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, UnlitMaterial);
	BlockMesh->SetupAttachment(DummyRoot);

	// Create Empty HUD
	HUDComponent = Cast< UAutoScalingHUD >(
		CreateDefaultSubobject(TEXT("HUD"), UWidgetComponent::StaticClass(), Assets()->HUD.ASH.Class.Get(), true, false)
	);


	//FOutputDeviceNull OutputDeviceNull;
	//HUDComponent->CallFunctionByNameWithArguments(TEXT("UpdateWidgetRender"), OutputDeviceNull, nullptr, true);

	//HUDComponent = Cast< UAutoScalingHUD >(DuplicateObject(Assets()->HUD.ASH.Get(), this));
	//HUDComponent = CreateDefaultSubobject<UAutoScalingHUD>(TEXT("HUD"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	SetActorTickEnabled(true);
}

void AHonoursProjBlock::Tick(float DeltaSeconds) {
	if (bIsActive) {
		SetActorLocation(MousePosWorld(GetWorld()) - clickOffset);
	}
}


AHonoursProjBlock* AHonoursProjBlock::HandleClick(UPrimitiveComponent* ClickedComponent) {
	bIsActive = !bIsActive;
	if (bIsActive) {
		clickOffset = MousePosWorld(GetWorld()) - GetActorLocation();
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
