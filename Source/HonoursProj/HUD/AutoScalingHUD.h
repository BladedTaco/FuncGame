// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"

#include "AutoScalingHUD.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class HONOURSPROJ_API UAutoScalingHUD : public UWidgetComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		bool UpdateSize = false;

public:

	UPROPERTY(EditAnywhere)
		FVector2D AspectRatio = FVector2D::UnitVector;

	UPROPERTY(EditAnywhere)
		FVector2D TargetSize = FVector2D(512, 512);


	void SizeToBounds(class UStaticMeshComponent* Mesh);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
