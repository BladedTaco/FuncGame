
#include "MyUtils.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

FVector MousePosWorld(UWorld* WorldContext) {
	if (!WorldContext) return FVector::ZeroVector;

	FVector worldPos, worldDir;
	auto playerCon = WorldContext->GetFirstPlayerController<APlayerController>();

	if (!playerCon) return FVector::ZeroVector;

	playerCon->DeprojectMousePositionToWorld(worldPos, worldDir);
	return worldPos;
}


FVector MousePosScreen(UWorld* WorldContext) {
	float mouseX, mouseY;
	WorldContext->GetFirstPlayerController()->GetMousePosition(mouseX, mouseY);
	return FVector(-mouseY, mouseX, 0);
}

void FitActorToPlane(AActor* actor, UStaticMeshComponent* plane) {
	// Get the Bounds for the Plane
	FVector PlaneMin, PlaneMax, PlaneRange, PlaneOrigin;
	plane->GetLocalBounds(PlaneMin, PlaneMax);
	PlaneRange = PlaneMax - PlaneMin;
	PlaneOrigin = (PlaneMax + PlaneMin) / 2;

	// Get the bounds for the Actor
	FVector ActorOrigin, ActorRange;
	actor->GetActorBounds(true, ActorOrigin, ActorRange);
	ActorRange *= 2;

	// Rescale the Actor to be contained by the Plane
	FVector scale = PlaneRange / ActorRange;
	scale.Z = scale.GetAbsMax();
	scale = FVector(scale.GetAbsMin());
	actor->SetActorScale3D(scale);
	// Move the Actor to be placed on the Plane
	actor->SetActorRelativeLocation(PlaneOrigin + scale.Z * ActorRange.Z / 2 - ActorOrigin);
	// Attach the Actor
	actor->AttachToComponent(plane, FAttachmentTransformRules::KeepRelativeTransform);
}
