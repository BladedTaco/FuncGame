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

#include "Types/TypeRepr.h"

#include "HUD/ParameterHUD.h"


#if WITH_EDITOR
#include "Editor.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/CompilerResultsLog.h"
#endif

#include "MyUtils.h"


// Sets default values
AFunctionConnector::AFunctionConnector() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// change materials
	ActiveMaterial = LitMaterial = Assets()->Material.White.Get();
	UnlitMaterial = Assets()->Material.Grey.Get();
	ConnectMaterial = Assets()->Material.Pink.Get();

	// Create static mesh component
	auto blockMesh = GetBlockMesh();
	blockMesh->SetStaticMesh(Assets()->Mesh.PuzzleCube.Get());
	blockMesh->SetRelativeScale3D(FVector(1, 3, 1) * FVector(0.2f, 0.2f, 0.2f));
	blockMesh->SetMaterial(0, UnlitMaterial);

	// Create Connector
	ConnectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMesh0"));
	ConnectMesh->SetStaticMesh(Assets()->Mesh.Cylinder.Get());
	ConnectMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	ConnectMesh->SetRelativeLocation(FVector(0, 0, 32.0f));
	ConnectMesh->SetMaterial(0, UnlitMaterial);
	ConnectMesh->SetVisibility(false);
	ConnectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//ConnectMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	ConnectMesh->SetupAttachment(RootComponent);

	// Create HUD.Component
	HUD.UpdateComponent(GetHUDComponent());
	HUD.Component->SetRelativeLocation(FVector::UpVector * 200.0f);
	HUD.Component->SetWorldRotation(FRotator(90, 0, 180));
	HUD.Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HUD.Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HUD.Component->SetDrawAtDesiredSize(true);
	HUD.Component->SetupAttachment(RootComponent);
	HUD.Component->SetWidgetClass(Assets()->HUD.Parameter.Class);
	HUD.Component->SizeToBounds(blockMesh);
}


void AFunctionConnector::SetupHUD() {
	HUD.UpdateComponent(GetHUDComponent());

	HUD.Component->AspectRatio = FVector2D(3, 1);
	//HUD.Component->InitWidget();
	//HUD.Component->UpdateWidget();
	HUD.Component->SizeToBounds(GetBlockMesh());

	if (ParameterInfo.Type && HUD.Inst().IsValid()) {
		HUD.Instance->Name = ParameterInfo.Name;
		HUD.Instance->Type = ParameterInfo.Type->ToString();
	}
}


void AFunctionConnector::BeginPlay() {
	Super::BeginPlay();

	SetupHUD();


	ResolveType();
	GetValue();
}

void AFunctionConnector::PostLoad() {
	Super::PostLoad();

	// Dispatch Delegate on 0.5s delay, without looping
	GetWorld()->GetTimerManager().SetTimer(
		AFunctionConnector::SpawnAllReprTimerHandle,
		FTimerDelegate::CreateUFunction(this, FName("SpawnAllRepr")), 
		0.5f, false
	);

	// Next tick, align connectors
	GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {
		if (IsValid(this->Function)) {
			FVector min, max, extent;
			this->Function->GetBlockMesh()->GetLocalBounds(min, max);
			FVector newLoc = this->GetActorLocation();
			newLoc.Z = this->Function->GetActorLocation().Z + extent.Z;
			this->SetActorLocation(newLoc);
		}
	});
}

void AFunctionConnector::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

#if WITH_EDITOR
	GEngine->OnLevelActorDetached().AddLambda([](AActor* me, const AActor* attach) { 
		TArray<AActor*> actors;
		me->GetAttachedActors(actors);
		for (auto* actor : actors) {
			actor->Destroy();
		}
		me->Destroy(); 
	});
#endif

	if (!ParameterInfo.Type) {
		ParameterInfo.Type = UTypeConst::New(ETypeBase::NONE);
	}

	SetupHUD();
	Tick(0.1f);
}

void AFunctionConnector::BeginDestroy() {
	if (Function) {
		Function->InputBlocks.Remove(Cast<AFunctionInput>(this));
		Function->OutputBlocks.Remove(Cast<AFunctionOutput>(this));
	}
	Super::BeginDestroy();
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
	AActor::Tick(DeltaSeconds);
	if (bIsActive) {
		FVector me = GetBlockMesh()->GetComponentLocation();
		FVector mouse = MousePosWorld(GetWorld());
		mouse.Z = me.Z = ConnectMesh->GetComponentLocation().Z;
		ConnectMesh->SetWorldTransform(Connect(me, mouse));
	}

	SetupHUD();
}

UType* AFunctionConnector::ResolveType() {
	UType* type = ResolveType_Impl();
	SpawnRepr(type);
	return type;
}

VStar AFunctionConnector::GetValue() {
	VStar value;
	if (Function->IsStatus(EPropagable::VALID)) {
		value = GetValue_Impl();
	}

	TypeRepr->UpdateValue(value);
	return value;
}


AHonoursProjBlock* AFunctionConnector::HandleClick(UPrimitiveComponent* ClickedComponent) {
	bIsActive = !bIsActive;
	if (bIsActive) {
		ConnectMesh->SetVisibility(true);
		ConnectMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		clickOffset = MousePosWorld(GetWorld()) - GetActorLocation();

		// Get All connectable actors
		TArray<AActor*> actors;
		TSubclassOf<AActor> cls = IsA<AFunctionInput>() ? AFunctionOutput::StaticClass() : AFunctionInput::StaticClass();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), cls, actors);

		UType* myType = ResolveType();
		for (AActor* act : actors) {

			//// Skip Leftwards Actors
			//if ((act->GetActorLocation() - GetActorLocation()).Y < 10) {
			//	continue;
			//}

			// Get other and its type
			auto other = Cast<AFunctionConnector>(act);
			UType* otherType = other->ResolveType()->VolatileConst();

			// Skip Shared Connectors
			if (other->Function == Function) {
				continue;
			}


			//// Get Applicability
			//bool applicable;
			//if (IsA<AFunctionInput>()) {
			//	applicable = myType->Supercedes(otherType);
			//} else {
			//	applicable = otherType->Supercedes(myType);
			//}
			
			//bool applicable = myType->Supercedes(otherType) || otherType->Supercedes(myType);

			bool applicable = myType->VolatileConst()->UnifyWith(otherType);


			//UE_LOG(LogTemp, Warning, TEXT("SUPERCEDES? %d"), applicable);

			// Highlight Applicable
			if (applicable) {
				//UE_LOG(LogTemp, Warning, TEXT("Applicable"));
				ValidConnections.Add(other);
				other->GetBlockMesh()->SetMaterial(0, other->ConnectMaterial);
				// TODO: APPLY EVIDENCE
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

	if (HUD.Instance.IsValid()) {
		HUD.Instance->Type = ResolveType()->ToString();
		// Proprogate
		Function->Propagate({ EPropagable::DIRTY });
	}


	return this;
}

void AFunctionConnector::EditorConnectTo() {
	if (!EditorConnect.IsValid() || !EditorConnect->GetBlockMesh()) {
		UE_LOG(LogTemp, Warning, TEXT("Invalid EditorConnect for AFunctionConnector::EditorConnectTo"));
		HandleRClick(GetBlockMesh());
		HandleRClick(GetBlockMesh());
		this->Tick(0.1f);
		return;
	}

	// Select This
	HandleClick(GetBlockMesh());
	// Drag to EditorConnect
	HandleClick(EditorConnect->GetBlockMesh());

	this->Tick(0.1f);
	EditorConnect->Tick(0.1f);
}


void AFunctionConnector::SpawnRepr(UType* Type) {

	// Update or Create Repr
	if (TypeRepr && IsValid(TypeRepr)) {
		// Update Existing Repr
		auto newRepr = TypeRepr->UpdateRepr(Type);
		if (TypeRepr == newRepr) return; // Do Nothing on Identical
		TypeRepr = newRepr;
	} else {
		// Spawn new Repr
		TypeRepr = ATypeRepr::CreateRepr(Type, GetWorld());
	}


	// Fit to Plane and Move Up
	FitActorToPlane(TypeRepr, TypeRepr->BoundingBox, GetBlockMesh());
	TypeRepr->AddActorLocalOffset(FVector::UpVector * 1000);

	if (!ConnectorIconDisplay) TypeRepr->UpdateVisibility(false);
}

void AFunctionConnector::SpawnAllRepr() {
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), actors);

	for (auto actor : actors) {
		Cast<AFunctionConnector>(actor)->ResolveType();
	}

}