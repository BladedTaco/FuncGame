// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HonoursProjBlock.generated.h"

/** A block that can be clicked */
UCLASS(MinimalAPI)
class AHonoursProjBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

protected:
	/** HUD component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UAutoScalingHUD* HUDComponent;

public:
	AHonoursProjBlock();

	/** Are we currently active? */
	bool bIsActive;

	/** Pointer to white material used on the focused block */
	UPROPERTY(Category = BlockMaterials, VisibleAnywhere)
	class UMaterialInstance* LitMaterial;

	/** Pointer to blue material used on inactive blocks */
	UPROPERTY(Category = BlockMaterials, VisibleAnywhere)
	class UMaterialInstance* UnlitMaterial;

	/** Pointer to orange material used on active blocks */
	UPROPERTY(Category = BlockMaterials, VisibleAnywhere)
	class UMaterialInstance* ActiveMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class AHonoursProjBlockGrid* OwningGrid;

	void Highlight(bool bOn);

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UAutoScalingHUD* GetHUDComponent() const { return HUDComponent; }

	void Tick(float DeltaSeconds);
	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent);
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent);

	FVector clickOffset = FVector::ZeroVector;
};



