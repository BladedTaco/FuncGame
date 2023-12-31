
#include "MyUtils.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

FVector MousePosWorld(UWorld* WorldContext) {
	if (!WorldContext) return FVector::ZeroVector;

	FVector worldPos, worldDir;
	auto playerCon = WorldContext->GetFirstPlayerController<APlayerController>();

	if (!playerCon) return FVector::ZeroVector;

	playerCon->DeprojectMousePositionToWorld(worldPos, worldDir);
	return worldPos;
}


FVector MousePosScreen(UWorld* WorldContext) {
	if (!WorldContext || !IsValid(WorldContext)) return FVector::ZeroVector;

	if (auto PC = WorldContext->GetFirstPlayerController()) {
		float mouseX, mouseY;
		PC->GetMousePosition(mouseX, mouseY);
		return FVector(-mouseY, mouseX, 0);
	}
	return FVector::ZeroVector;
}

void FitActorToPlane(AActor* Actor, UStaticMeshComponent* Plane) {
	// Get the bounds for the Actor
	FVector ActorOrigin, ActorRange;
	Actor->GetActorBounds(false, ActorOrigin, ActorRange);
	ActorRange *= 2;

	FitActorToPlane(Actor, ActorOrigin, ActorRange, Plane);
}

void FitActorToPlane(AActor* Actor, UBoxComponent* ActorBounds, UStaticMeshComponent* Plane) {
	FitActorToPlane(
		Actor, 
		ActorBounds->GetComponentLocation(),
		ActorBounds->GetScaledBoxExtent() * 2,
		Plane
	);
}


void FitActorToPlane(AActor* Actor, FVector ActorOrigin, FVector ActorRange, UStaticMeshComponent* Plane) {

	Actor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Actor->SetActorLocation(FVector::ZeroVector);

	FVector ActorOriginOffset = Actor->GetActorLocation() - ActorOrigin;

	// Get the Bounds for the Plane
	FVector PlaneMin, PlaneMax, PlaneRange, PlaneOrigin, PlaneScale;
	Plane->GetLocalBounds(PlaneMin, PlaneMax);
	PlaneRange = PlaneMax - PlaneMin;
	PlaneOrigin = (PlaneMax + PlaneMin) / 2;

	// Get PlaneScale as Ratio with standard as 1.0f
	PlaneScale = Plane->GetComponentScale();
	PlaneScale.Z = PlaneScale.GetAbsMax();
	PlaneScale /= PlaneScale.GetAbsMin();
	PlaneScale.Z = 1.0f;

	// Rescale the Actor to be contained by the Plane
	FVector scale = (PlaneRange * PlaneScale) / ActorRange;
	scale.Z = scale.GetAbsMax();
	scale = FVector(scale.GetAbsMin());

	scale /= PlaneScale;

	Actor->SetActorScale3D(scale);

	// Move the Actor to be placed on the Plane
	ActorOrigin.Z -= ActorRange.Z * scale.Z;
	PlaneOrigin.Z += PlaneRange.Z / 2;
	//Actor->SetActorLocation(PlaneOrigin - ActorOrigin);
	Actor->SetActorLocation(
		PlaneOrigin // From Plane Origin
		+ (ActorOriginOffset * scale) // Shift to align ActorOrigin and PlaneOrigin
		+ (FVector::UpVector * ActorRange.Z * scale.Z / 2) // Shift Up to Place On Top
	);

	// Attach the Actor
	Actor->AttachToComponent(Plane, FAttachmentTransformRules::KeepRelativeTransform);
}
