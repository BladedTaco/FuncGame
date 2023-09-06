#include "HUDBlock.h"

#include "AssetLoader_gen.h"
#include "HUD/AutoScalingHUD.h"

AHUDBlock::AHUDBlock() {

	// Create Empty HUD
	HUDComponent = Cast< UAutoScalingHUD >(
		CreateDefaultSubobject(TEXT("HUD"), UWidgetComponent::StaticClass(), Assets()->HUD.ASH.Class.Get(), true, false)
	);

}

void AHUDBlock::EndPlay(EEndPlayReason::Type EndPlayReason) {
	if (HUDComponent) {
		HUDComponent->DestroyComponent(false);
		HUDComponent = NULL;
	}
	Super::EndPlay(EndPlayReason);
}