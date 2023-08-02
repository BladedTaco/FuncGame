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
	virtual bool ShouldActivate() const override { return true;  }

	UPROPERTY(EditAnywhere)
		FVector2D AspectRatio = FVector2D::UnitVector;

	UPROPERTY(EditAnywhere)
		FVector2D TargetSize = FVector2D(512, 512);

	UAutoScalingHUD();

	void SizeToBounds(class UStaticMeshComponent* Mesh);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnComponentCreated() override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;
	virtual void BeginDestroy() override;
};

// Generic Version
USTRUCT(BlueprintType)
struct FGeneric3DHUD {
	GENERATED_BODY()
private:
	inline static TMap<UBlueprint*, FTimerHandle> Compiled = {};
	static void CompileBlueprint(UBlueprint* BlueprintObj);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<UAutoScalingHUD> Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TWeakObjectPtr<UUserWidget> GenericInstance;
public:
	// Base Constructor
	FGeneric3DHUD()
		: Component(NULL)
		, GenericInstance(NULL) {};
public:
	virtual void UpdateInstance();
	void UpdateComponent(UAutoScalingHUD* InComponent);

	void RecompileInstanceClass();
	static void UpdateInEditor(UClass* cls, bool Force = false);
};

// Templated Version
template <class HUDClass>
struct THUD : public FGeneric3DHUD {
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TWeakObjectPtr<HUDClass> Instance;
public:
	// Base Constructor
	THUD() : Instance(NULL) {};
public:
	virtual void UpdateInstance() override {
		FGeneric3DHUD::UpdateInstance();
		Instance = MakeWeakObjectPtr<HUDClass>( Cast<HUDClass>(Component->GetUserWidgetObject()) );
	}

	TWeakObjectPtr<HUDClass> Inst() {
		UpdateInstance();
		return Instance;
	}

};