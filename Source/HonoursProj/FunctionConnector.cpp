// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionConnector.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Materials/Material.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"


// Sets default values
AFunctionConnector::AFunctionConnector() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> CylinderMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> UnlitMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, CylinderMesh(TEXT("/Game/MyContent/Meshes/Cylinder.Cylinder"))
			, UnlitMaterial(TEXT("/Game/Puzzle/Meshes/GreyMaterial.GreyMaterial")) {}
	};
	static FConstructorStatics ConstructorStatics;

	// change materials
	ActiveMaterial = LitMaterial;
	UnlitMaterial = ConstructorStatics.UnlitMaterial.Get();

	// Create static mesh component
	auto BlockMesh = GetBlockMesh();
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	BlockMesh->SetMaterial(0, UnlitMaterial);

	//RootComponent = BlockMesh;

	// Create Connector
	ConnectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMesh0"));
	ConnectMesh->SetStaticMesh(ConstructorStatics.CylinderMesh.Get());
	ConnectMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	ConnectMesh->SetRelativeLocation(FVector(0, 0, 32.0f));
	ConnectMesh->SetMaterial(0, UnlitMaterial);
	ConnectMesh->SetVisibility(false);
	ConnectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConnectMesh->AttachTo(RootComponent);

}


FTransform AFunctionConnector::Connect(FVector a, FVector b) {
	return FTransform(
		// rotated from Start towards End
		FQuat((b - a).GetSafeNormal().RotateAngleAxis(90, FVector::UpVector), PI / 2),
		// At the midway point
		FVector(a + b) / 2,
		// Scaled to reach both
		FVector(0.1f, 0.1f, (b - a).Size() / 100.0f)
	);
}

void AFunctionConnector::Tick(float DeltaSeconds) {
	if (bIsActive) {
		FVector me = GetBlockMesh()->GetComponentLocation();
		FVector mouse = MousePos();
		mouse.Z = me.Z = ConnectMesh->GetComponentLocation().Z;
		ConnectMesh->SetWorldTransform(Connect(me, mouse));
	}
}


AHonoursProjBlock* AFunctionConnector::HandleClick(UPrimitiveComponent* ClickedComponent) {
	bIsActive = !bIsActive;
	if (bIsActive) {
		ConnectMesh->SetVisibility(true);
		clickOffset = MousePos() - GetActorLocation();
	}
	return this;
}
