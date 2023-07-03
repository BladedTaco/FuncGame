// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionConnector.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Materials/Material.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Kismet/GameplayStatics.h"

#include "AssetLoader_gen.h"

// Sets default values
AFunctionConnector::AFunctionConnector() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// change materials
	ActiveMaterial = LitMaterial = Assets.Material.White.Get();
	UnlitMaterial = Assets.Material.Grey.Get();
	ConnectMaterial = Assets.Material.Pink.Get();

	// Create static mesh component
	auto blockMesh = GetBlockMesh();
	blockMesh->SetStaticMesh(Assets.Mesh.PuzzleCube.Get());
	blockMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	blockMesh->SetMaterial(0, UnlitMaterial);

	// Create Connector
	ConnectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMesh0"));
	ConnectMesh->SetStaticMesh(Assets.Mesh.Cylinder.Get());
	ConnectMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	ConnectMesh->SetRelativeLocation(FVector(0, 0, 32.0f));
	ConnectMesh->SetMaterial(0, UnlitMaterial);
	ConnectMesh->SetVisibility(false);
	ConnectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConnectMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

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

		// Get All connectable actors
		TArray<AActor*> actors;
		TSubclassOf<AActor> cls = IsA<AFunctionInput>() ? AFunctionOutput::StaticClass() : AFunctionInput::StaticClass();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), cls, actors);

		UType* myType = ResolveType();
		for (AActor* act : actors) {
			// Skip Leftwards Actors
			if ((act->GetActorLocation() - GetActorLocation()).Y < 10) {
				continue;
			}

			// Get other and its type
			auto other = Cast<AFunctionConnector>(act);
			UType* otherType = other->ResolveType();
			
			// Get Applicability
			bool applicable;
			if (IsA<AFunctionInput>()) {
				applicable = myType->Supercedes(otherType);
			} else {
				applicable = otherType->Supercedes(myType);
			}

			UE_LOG(LogTemp, Warning, TEXT("SUPERCEDES? %d"), applicable);

			// Highlight Applicable
			if (applicable) {
				UE_LOG(LogTemp, Warning, TEXT("Applicable"));
				ValidConnections.Add(other);
				other->GetBlockMesh()->SetMaterial(0, other->ConnectMaterial);
			}
		}

		GetBlockMesh()->SetMaterial(0, UnlitMaterial);
	} else {
		// Clear Connections
		for (auto other : ValidConnections) {
			other->GetBlockMesh()->SetMaterial(0, other->UnlitMaterial);
		}
		ValidConnections = {};

	}


	return this;
}
