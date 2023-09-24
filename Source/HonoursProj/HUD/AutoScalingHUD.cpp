// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoScalingHUD.h"

#include "Components/StaticMeshComponent.h"
#include "Blueprint/WidgetTree.h"

#include "MyUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Rendering/SlateRenderer.h"

#if WITH_EDITOR
#include "Editor.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/CompilerResultsLog.h"
#endif


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

UAutoScalingHUD::UAutoScalingHUD() {
	SetDrawAtDesiredSize(false);

	//PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.bStartWithTickEnabled = true;
	//PrimaryComponentTick.SetTickFunctionEnable(true);
	//PrimaryComponentTick.bTickEvenWhenPaused = true;
	//bTickInEditor = true;
	//bAutoActivate = true;
	//SetComponentTickEnabled(true);
	//TickWhenOffscreen = true;
	//
	//RedrawTime = 1.0f;

	
}

void UAutoScalingHUD::InvalidateAllWidgets() {
	for (UAutoScalingHUD* HUD : AllHUDs) {
		if (IsValid(HUD) && HUD->IsValidLowLevel() && IsValid(HUD->LastBounds)) {
			HUD->SizeToBounds(HUD->LastBounds);
		}
	}
}

void UAutoScalingHUD::SizeToBounds(UStaticMeshComponent* Mesh) {
	
	if (!IsValid(this) || OwnerNeedsInitialization() || !IsValid(GetOwner()) || !IsValid(Mesh)) return;

	LastBounds = Mesh;


	//FSlateApplicationBase::Get().GetRenderer()->GetFontAtlasProvider()->
	//	->DestroyCachedFastPathElementData(CachedElementData);

	// Get Size
	FVector min, max;
	Mesh->GetLocalBounds(min, max);
	FVector2D HUDSize = FVector2D((max - min) * Mesh->GetComponentScale());
	
	FVector MidPos = GetOwner()->GetActorLocation();
	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector2D minPos, maxPos;
	UGameplayStatics::ProjectWorldToScreen(controller, MidPos + min, minPos);
	UGameplayStatics::ProjectWorldToScreen(controller, MidPos + max, maxPos);

	int MaxSize = (maxPos - minPos).GetMax();
	
	MaxSize = FMath::Clamp(MaxSize, 50, 1000);

	// Set Aspect Ratio
	//TargetSize = HUDSize * (50 / HUDSize.GetMin());
	TargetSize = HUDSize * (MaxSize / HUDSize.GetMax());

	// Scale Component
	FVector2D Scale = (HUDSize / GetCurrentDrawSize()) / HUDSize.GetSafeNormal();
	Scale = FVector2D(Scale.GetMin());
	SetWorldScale3D(FVector(1.0f, Scale.Y, Scale.X));

	// Update Size on Next opportunity
	//UpdateSize = true;
	SetDrawAtDesiredSize(false);


	SetDrawSize(FVector2D(TargetSize.Y, TargetSize.X));

}

void UAutoScalingHUD::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdateSize) {
		// Get Size
		FVector2D currSize = GetCurrentDrawSize();

		// When Valid
		if (!currSize.IsNearlyZero()) {
			SetDrawSize(FVector2D(TargetSize.Y, TargetSize.X));
			UpdateSize = false;
		}
	}
}

void UAutoScalingHUD::OnComponentCreated() {
	Super::OnComponentCreated();

	UAutoScalingHUD::AllHUDs.Add(this);

	InitWidget();
	UpdateWidget();

	FGeneric3DHUD::UpdateInEditor(UAutoScalingHUD::StaticClass());
	FGeneric3DHUD::UpdateInEditor(GetWidgetClass());
}

void UAutoScalingHUD::DestroyComponent(bool bPromoteChildren) {
	UAutoScalingHUD::AllHUDs.Remove(this);

	if (auto widget = GetUserWidgetObject()) {
		widget->ReleaseSlateResources(true);
		widget->RemoveFromParent();
	}
	Super::DestroyComponent(bPromoteChildren);
}

void UAutoScalingHUD::BeginDestroy() {
	if (auto widget = GetUserWidgetObject()) {
		SetWidget(nullptr);
		//GetSlateWindow()->RequestDestroyWindow();
		RemoveWidgetFromScreen();
		widget->ReleaseSlateResources(true);
		widget->RemoveFromViewport();
		widget->RemoveFromRoot();
		//widget->Destruct();
	}
	Super::BeginDestroy();
}


// FGeneric3DHUD impls

// Updates the HUD.Instance based on HUD.Component
void FGeneric3DHUD::UpdateInstance() {
	// Get current
	auto newInst = MakeWeakObjectPtr(Component->GetUserWidgetObject());
	// If different
	if (newInst.Get() != GenericInstance.Get()) {
		// Update
		GenericInstance = newInst;
		// Recompile Blueprint
		RecompileInstanceClass();
	}
}

// Sets the new HUD.Component
void FGeneric3DHUD::UpdateComponent(UAutoScalingHUD* InComponent) {
	Component = MakeWeakObjectPtr(InComponent);
	Component->InitWidget();
	UpdateInstance();
}

void FGeneric3DHUD::RecompileInstanceClass() {
	if (!GenericInstance.IsValid()) return;
	UClass* cls = GenericInstance->GetClass();
	UpdateInEditor(cls);
}

void FGeneric3DHUD::CompileBlueprint(UBlueprint* BlueprintObj) {
#if WITH_EDITOR
	FCompilerResultsLog LogResults;
	LogResults.SetSourcePath(BlueprintObj->GetPathName());
	LogResults.BeginEvent(TEXT("Compile"));

	EBlueprintCompileOptions CompileOptions = EBlueprintCompileOptions::None;
	FKismetEditorUtilities::CompileBlueprint(BlueprintObj, CompileOptions, &LogResults);

	LogResults.EndEvent();
#endif
}

	// Makes HUD update while in editor
void FGeneric3DHUD::UpdateInEditor(UClass* cls, bool Force) {
#if WITH_EDITOR
	// Require Editor, and Class
	if (!GIsEditor || !GEditor || !GWorld || GWorld->HasBegunPlay()) return;
	if (!IsValid(cls)) return;

	// Require Blueprint
	auto BlueprintObj = Cast<UBlueprint>(cls->ClassGeneratedBy);
	if (!BlueprintObj) return;

	// Get Cached or New Timer
	FTimerHandle timer = Compiled.FindOrAdd(BlueprintObj);

	// Dispatch Delegate on 0.5s delay, without looping
	GEditor->GetTimerManager()->SetTimer(timer, FTimerDelegate::CreateLambda(
		[BlueprintObj]() {
			FGeneric3DHUD::CompileBlueprint(BlueprintObj);
			FGeneric3DHUD::Compiled.Remove(BlueprintObj);
			UE_LOG(LogTemp, Warning, TEXT("Execute Compile"));
		}
	), 0.5f, false);

	// Repush Timer
	Compiled.Add(BlueprintObj, timer);
#endif
}