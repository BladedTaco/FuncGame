// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HonoursProjPawn.generated.h"

UCLASS(config=Game)
class AHonoursProjPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	void RemoveInactive();

protected:
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	void OnLClickPress();
	void OnLClickRelease();

	void OnRClickPress();
	void OnRClickRelease();

	void OnScroll(float axis);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class AHonoursProjBlock* CurrentBlockFocus;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TWeakObjectPtr<UPrimitiveComponent> CurrentComponentFocus;

	UPROPERTY(VisibleAnywhere)
	TArray<AHonoursProjBlock*> SelectedBlocks;
};
