
#include "MyUtils.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

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