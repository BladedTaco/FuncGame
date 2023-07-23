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

	UAutoScalingHUD();

	void SizeToBounds(class UStaticMeshComponent* Mesh);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};

template <class HUDClass>
struct THUD {
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<UAutoScalingHUD> Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TWeakObjectPtr<HUDClass> Instance;

public:
	// Base Constructor
	THUD()
		: Component(NULL)
		, Instance(NULL) {};

public:
	void UpdateInstance() {
		Instance = MakeWeakObjectPtr( Cast<HUDClass>(Component->GetUserWidgetObject()) );
	}
	void UpdateComponent(UAutoScalingHUD* InComponent) {
		Component = MakeWeakObjectPtr(InComponent);
	}
};
