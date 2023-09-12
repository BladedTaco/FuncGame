// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationBoundsComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULocationBoundsComponent::ULocationBoundsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bTickEvenWhenPaused = false;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	bTickInEditor = false;

	// ...
}

void ULocationBoundsComponent::SetBounds(AActor* ActorBounds, FVector Offset) {
	// Get Vectors
	FVector Origin, BoxExtent;
	ActorBounds->GetActorBounds(false, Origin, BoxExtent);

	// Set Vectors
	MinPosition = Origin - BoxExtent;
	MaxPosition = Origin + BoxExtent;
	SpaceType = ESpaceType::WorldSpace;
}

void ULocationBoundsComponent::SetBounds(FVector2D ScreenMinimum, FVector2D ScreenMaximum, float ScreenDepth) {
	// Set Vectors
	MinPosition = FVector(ScreenMinimum, ScreenDepth);
	MaxPosition = FVector(ScreenMaximum, ScreenDepth);
	SpaceType = ESpaceType::ScreenSpace;
	AxisLimits = EAxisFlags::XY;
}

void ULocationBoundsComponent::SetBounds(FVector LocalMinimum, FVector LocalMaximum) {
	// Set Vectors
	MinPosition = LocalMinimum;
	MaxPosition = LocalMaximum;
	SpaceType = ESpaceType::LocalSpace;

	// Convert to World Space
	ConvertLocalToWorldSpace();
}

void ULocationBoundsComponent::SetBounds(UBoxComponent* Bounds, FVector Offset) {
	// Get Vectors
	FVector Origin = Bounds->GetComponentLocation();
	FVector BoxExtent = Bounds->GetScaledBoxExtent();

	// Set Vectors
	MinPosition = Origin - BoxExtent;
	MaxPosition = Origin + BoxExtent;
	SpaceType = ESpaceType::WorldSpace;
}

void ULocationBoundsComponent::SetBounds(ULocationBoundsComponent* CopyFrom) {
	// Set Vectors
	MinPosition = CopyFrom->MinPosition;
	MaxPosition = CopyFrom->MaxPosition;
	SpaceType = CopyFrom->SpaceType;
}


void ULocationBoundsComponent::ConvertLocalToWorldSpace() {
	// Only Valid if Space is Local Space and During Play
	if (SpaceType != ESpaceType::LocalSpace || !HasBegunPlay()) return;

	// Convert Local Space to World Space
	MinPosition += GetOwner()->GetActorLocation();
	MaxPosition += GetOwner()->GetActorLocation();
	SpaceType = ESpaceType::WorldSpace;
}

void ULocationBoundsComponent::ApplyNewPosition(FVector BoundedPosition) {
	// Get Current Actors Location
	FVector CurrentPosition = GetOwner()->GetActorLocation();

	// Reset Unbounded Axes
	if (!EnumHasAnyFlags(AxisLimits, EAxisFlags::X)) BoundedPosition.X = CurrentPosition.X;
	if (!EnumHasAnyFlags(AxisLimits, EAxisFlags::Y)) BoundedPosition.Y = CurrentPosition.Y;
	if (!EnumHasAnyFlags(AxisLimits, EAxisFlags::Z)) BoundedPosition.Z = CurrentPosition.Z;

	// Early Exit on No bounding
	if (CurrentPosition == BoundedPosition) return;

	// Update the Location to Bounded Location
	GetOwner()->SetActorLocation(BoundedPosition);
}

// Called when the game starts
void ULocationBoundsComponent::BeginPlay()
{
	Super::BeginPlay();

	// Order Bounds Tick by Priority
	TArray<ULocationBoundsComponent*> BoundsComponents;
	GetOwner()->GetComponents(BoundsComponents);
	for (auto Component : BoundsComponents) {
		// Bounds Components with a higher Bounds Priority
		if (IsValid(Component) && Component->BoundPriority < BoundPriority) {
			// Are forced to tick last, having more effect on final position
			AddTickPrerequisiteComponent(Component);
		}
	}

	ConvertLocalToWorldSpace();
	
}


// Called every frame
void ULocationBoundsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Exit on no owner or not during play
	if (!GetOwner() || !GetOwner()->HasActorBegunPlay()) return;

	// Get Actor Location
	FVector CurrentActorLocation = GetOwner()->GetActorLocation();

	if (SpaceType == ESpaceType::ScreenSpace) {
		// Get Player Controller
		auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		// Get Actor Location on Screen
		FVector2D ScreenPosition;
		UGameplayStatics::ProjectWorldToScreen(Controller, CurrentActorLocation, ScreenPosition);
		
		// Bound Actor Location in Screen Space
		FVector2D BoundPosition = FVector2D(FVector(ScreenPosition, 0).BoundToBox(MinPosition, MaxPosition));

		// Convert Bound Location to World Space
		FVector WorldPosition, _;
		UGameplayStatics::DeprojectScreenToWorld(Controller, BoundPosition, WorldPosition, _);

		// Clamp to Bounds
		ApplyNewPosition(WorldPosition);

	} else {
		// Clamp to Bounds
		ApplyNewPosition(CurrentActorLocation.BoundToBox(MinPosition, MaxPosition));
	}
}

