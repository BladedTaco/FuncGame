// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LocationBoundsComponent.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class ESpaceType : uint8 {
	WorldSpace,
	LocalSpace,
	ScreenSpace
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EAxisFlags : uint8 {
	None	= 0,
	X		= 1 << 0,
	Y		= 1 << 1,
	Z		= 1 << 2,
	XY		= X | Y,
	XZ		= X | Z,
	YZ		= Y | Z,
	XYZ		= X | Y | Z		
}; 
ENUM_CLASS_FLAGS(EAxisFlags);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HONOURSPROJ_API ULocationBoundsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULocationBoundsComponent();

	UPROPERTY(EditAnywhere)
	ESpaceType SpaceType;

	UPROPERTY(EditAnywhere, Meta = (Bitmask, BitmaskEnum = "EAxisFlags"))
	EAxisFlags AxisLimits = EAxisFlags::XYZ;

	UPROPERTY(EditAnywhere, meta = (ClampMin="-100", ClampMax="100"))
	int BoundPriority = 0;

public:
	void SetBounds(AActor* ActorBounds, FVector Offset = FVector::ZeroVector);
	void SetBounds(FVector2D ScreenMinimum, FVector2D ScreenMaximum, float ScreenDepth = 100.0f);
	void SetBounds(FVector LocalMinimum, FVector LocalMaximum);
	void SetBounds(UBoxComponent* Bounds, FVector Offset = FVector::ZeroVector);
	void SetBounds(ULocationBoundsComponent* CopyFrom);

protected:
	UPROPERTY(EditAnywhere)
	FVector MinPosition;

	UPROPERTY(EditAnywhere)
	FVector MaxPosition;

protected:
	// Convert Local Space Bound Positions to World Space Bound Positions
	void ConvertLocalToWorldSpace();
	// Apply and Modify BoundedPosition based on Axis Limits
	void ApplyNewPosition(FVector BoundedPosition);

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
