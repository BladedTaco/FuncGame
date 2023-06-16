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
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> CylinderMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> LitMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, CylinderMesh(TEXT("/Game/MyContent/Meshes/Cylinder.Cylinder"))
			, LitMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial")) {}
	};
	static FConstructorStatics ConstructorStatics;


	// Create static mesh component
	auto BlockMesh = GetBlockMesh();
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	BlockMesh->SetMaterial(0, ConstructorStatics.LitMaterial.Get());

	//RootComponent = BlockMesh;

	// Create Connector
	ConnectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMesh0"));
	ConnectMesh->SetStaticMesh(ConstructorStatics.CylinderMesh.Get());
	ConnectMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	ConnectMesh->SetRelativeLocation(FVector(0, 0, 32.0f));
	ConnectMesh->SetMaterial(0, UnlitMaterial);
	ConnectMesh->SetVisibility(false);
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
	FVector me = GetBlockMesh()->GetComponentLocation();
	if (bIsActive) {
		FVector mouse = MousePos();
		mouse.Z = me.Z = ConnectMesh->GetComponentLocation().Z;
		ConnectMesh->SetWorldTransform(Connect(me, mouse));
	} else if (connectedTo) {
		FVector target = connectedTo->GetActorLocation();
		me.Z = target.Z = ConnectMesh->GetComponentLocation().Z;
		ConnectMesh->SetRelativeTransform(Connect(me, target));
	}
}


AHonoursProjBlock* AFunctionConnector::HandleClick(UPrimitiveComponent* ClickedComponent) {
	bIsActive = !bIsActive;
	if (bIsActive) {
		ConnectMesh->SetVisibility(true);
		clickOffset = MousePos() - GetActorLocation();
	} else {
		// Create Connections
		TArray<AActor*> overlaps;
		ConnectMesh->GetOverlappingActors(overlaps, AFunctionConnector::StaticClass());

		// Sort Candidate Connections so that closest is first
		overlaps.Sort([this](const AActor& a, const AActor& b) {
			return a.GetDistanceTo(this) < b.GetDistanceTo(this);
		});

		// Give Connection
		if (overlaps.IsValidIndex(0)) {
			UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));
			connectedTo = Cast<AFunctionConnector>(overlaps[0]);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("NO OVERLAP"));
			ConnectMesh->SetVisibility(false);
		}

	}
	return this;
}

AHonoursProjBlock* AFunctionConnector::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	connectedTo = NULL;
	return this;
}
