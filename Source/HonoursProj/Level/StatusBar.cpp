#include "Level/StatusBar.h"

#include "AssetLoader_gen.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"


void UStatusBarComponent::Configure(EStatusType InType, int InMaxValue, bool bStartsFull) {
	MaxValue = InMaxValue;
	CurrentValue = bStartsFull ? InMaxValue : 0;
	Type = InType;
	Colour = UStatusBarComponent::ColourMap[InType];
	Name = UEnum::GetDisplayValueAsText(InType).ToString();
	SetBarMaterial();
}

void UStatusBarComponent::Configure(FString InName, FColor InColour, int InMaxValue, bool bStartsFull) {
	MaxValue = InMaxValue;
	CurrentValue = bStartsFull ? InMaxValue : 0;
	Type = EStatusType::UNIQUE;
	Colour = InColour;
	Name = InName;
	SetBarMaterial();
}

// Sets default values for this component's properties
UStatusBarComponent::UStatusBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//// Create Bar Mesh
	//BarMesh = CreateDefaultSubobject<UStaticMeshComponent>(*GetFName().ToString().Append(TEXT("_BarMesh")));
	//// Create Backing Mesh
	//BackingMesh = CreateDefaultSubobject<UStaticMeshComponent>(*GetFName().ToString().Append(TEXT("_BackingMesh")));

	//// Do Shared Bar/Backing Configuration
	//for (auto& mesh : { BarMesh, BackingMesh }) {
	//	mesh->SetStaticMesh(Assets()->Mesh.OffsetCylinder.Get());
	//	mesh->SetWorldRotation(FQuat(FVector::ForwardVector, PI / 2));
	//	mesh->SetupAttachment(this);
	//	mesh->SetRelativeLocation(FVector::LeftVector * 500);
	//	//mesh->RegisterComponent();
	//}

	//// Create Bar Material
	////BarMaterial = UMaterialInstanceDynamic::Create(Assets()->Material.Base.Get(), BarMesh);

	//// Colour the Bars
	//BackingMesh->SetMaterial(0, Assets()->Material.Black.Get());
	////BarMesh->SetMaterial(0, BarMaterial);
	////BarMaterial = BarMesh->CreateDynamicMaterialInstance(0, Assets()->Material.Base.Get());

	////BarMaterial = UMaterialInstanceDynamic::Create(Assets()->Material.Base.Get(), NULL);
	////BarMesh->SetMaterial(0, BarMaterial);

	//// Bring BarMesh in front of BackingMesh
	//BarMesh->SetRelativeLocation(BarMesh->GetRelativeLocation() + FVector::UpVector * 10);

	//// Scale entire Scene Component
	//SetRelativeScale3D(FVector(0.1, 0.1, 3));

	OffsetCylinderMesh = Assets()->Mesh.OffsetCylinder.Get();
	BlackMaterial = Assets()->Material.Black.Get();
	BaseMaterial = Assets()->Material.Base.Get();
}

// Returns the Percentge of the Value
float UStatusBarComponent::GetPercentage() {
	return CurrentValue / MaxValue;
}

// Called when the game starts
void UStatusBarComponent::BeginPlay()
{
	Super::BeginPlay();


	// Create Bar Mesh
	BarMesh = NewObject<UStaticMeshComponent>(GetOuter(), *GetFName().ToString().Append(TEXT("_BarMesh")));
	// Create Backing Mesh
	BackingMesh = NewObject<UStaticMeshComponent>(GetOuter(), *GetFName().ToString().Append(TEXT("_BackingMesh")));

	// Do Shared Bar/Backing Configuration
	for (auto& mesh : { BarMesh, BackingMesh }) {
		mesh->SetStaticMesh(OffsetCylinderMesh);
		mesh->SetWorldRotation(FQuat(FVector::ForwardVector, PI / 2));
		mesh->SetupAttachment(this);
		mesh->SetRelativeLocation(FVector::LeftVector * 500);
		mesh->RegisterComponent();
	}

	// Colour the Bars
	BackingMesh->SetMaterial(0, BlackMaterial);
	SetBarMaterial();

	// Bring BarMesh in front of BackingMesh
	BarMesh->SetRelativeLocation(BarMesh->GetRelativeLocation() + FVector::UpVector * 10);

	// Scale entire Scene Component
	SetRelativeScale3D(FVector(0.1, 0.1, 3));

}


// Called every frame
void UStatusBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Rescale Bar
	if (CurrentValue != LastValue) {
		LastValue = CurrentValue;

		// Scale the Bar
		FVector newScale = BarMesh->GetRelativeScale3D();
		newScale.Z = GetPercentage();
		BarMesh->SetRelativeScale3D(newScale);
	}
}

void UStatusBarComponent::SetBarMaterial() {
	if (!IsValid(BarMesh)) return;

	UMaterialInstanceDynamic* BarMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, NULL);
	BarMaterial->SetVectorParameterValue(TEXT("DiffuseColor"), Colour);
	BarMesh->SetMaterial(0, BarMaterial);
}


