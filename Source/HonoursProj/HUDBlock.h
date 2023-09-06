#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"
#include "HUDBlock.generated.h"

// Honours Proj Block with Auto Scaling HUD
UCLASS(MinimalAPI)
class AHUDBlock : public AHonoursProjBlock 
{
	GENERATED_BODY()

public:
	AHUDBlock();

protected:
	/** HUD component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAutoScalingHUD* HUDComponent;

public:
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UAutoScalingHUD* GetHUDComponent() const { return HUDComponent; }

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
};