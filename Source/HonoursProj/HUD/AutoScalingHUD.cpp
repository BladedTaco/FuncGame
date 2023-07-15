// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/AutoScalingHUD.h"

#include "Components/StaticMeshComponent.h"
#include "Blueprint/WidgetTree.h"


//void UAutoScalingHUD::NativeOnInitialized() {
//	//Super::NativeOnInitialized();
//
//	UUserWidget::NativeOnInitialized();
//
//	Super::ForceLayoutPrepass();
//
//	//FVector2D targetSize = GetDesiredSize();
//
//	//FVector2D targetSize = GetRootWidget()->GetDesiredSize();
//	//
//
//	//float currAspect = targetSize.X / targetSize.Y;
//	//float targetAspect = AspectRatio.X / AspectRatio.Y;
//
//	//float XScale = (targetSize.Y * targetAspect) / targetSize.X;
//
//
//	//UE_LOG(LogTemp, Warning, TEXT("HUD Size: %s %f %f"), *widgets[0]->GetName(), targetSize.X, targetSize.Y);
//
//	//SetRenderScale(FVector2D(XScale, 1));
//
//}

void UAutoScalingHUD::SizeToBounds(UStaticMeshComponent* Mesh) {

	// Get Size
	FVector min, max;
	Mesh->GetLocalBounds(min, max);
	FVector2D HUDSize = FVector2D((max - min) * Mesh->GetComponentScale());
	// Set Size
	TargetSize = HUDSize;

	// Update Size on Next opportunity
	UpdateSize = true;
}

void UAutoScalingHUD::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdateSize) {
		// Get Size
		FVector2D currSize = GetCurrentDrawSize();

		// When Valid
		if (!currSize.IsNearlyZero()) {
			UE_LOG(LogTemp, Warning, TEXT("CurrSize, %f %f"), currSize.X, currSize.Y);

			FVector2D scale = TargetSize / currSize;
			SetRelativeScale3D(FVector(1.0f, scale.X, scale.Y));

			UpdateSize = false;
		}
	}


}
