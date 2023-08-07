// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"
#include "BlockFunction.h"


#include "HUD/AutoScalingHUD.h"
#include "HUD/ParameterHUD.h"

#include "FunctionConnector.generated.h"

class ATypeRepr;

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API AFunctionConnector : public AHonoursProjBlock {
	GENERATED_BODY()


public:
	// Parameter HUD
	//UPROPERTY(EditAnywhere)
		THUD<UParameterHUD> HUD;

	UPROPERTY(VisibleAnywhere)
		ABlockFunction* Function;


	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginDestroy() override;

	// Sets default values for this actor's properties
	AFunctionConnector();

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;


	UPROPERTY(Category = Connector, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ConnectMesh;

	FTransform Connect(FVector a, FVector b);

	void Tick(float DeltaSeconds);

	virtual UType* ResolveType() PURE_VIRTUAL(AFunctionConnector::ResolveType, return NULL;);
	virtual VStar GetValue() PURE_VIRTUAL(AFunctionConnector::GetValue, return VStar(););

	void SetupHUD();


public:
	UPROPERTY(Category = "Functions", EditAnywhere, BlueprintReadWrite, Transient, NonTransactional)
		TWeakObjectPtr<AFunctionConnector> EditorConnect;

	UFUNCTION(Category = "Functions", BlueprintCallable, CallInEditor)
		void EditorConnectTo();

public:
	UFUNCTION(Category = "Functions", BlueprintCallable, CallInEditor)
		void SpawnRepr();

	UFUNCTION(Category = "Functions", BlueprintCallable, CallInEditor)
		void SpawnAllRepr();

	UPROPERTY(VisibleAnywhere)
		ATypeRepr* TypeRepr;

public:
	UPROPERTY(VisibleAnywhere)
		FParameter ParameterInfo;
	UPROPERTY(VisibleAnywhere)
		int Index;

	/** Pointer to Yellow material used on Connectable Connectors */
	UPROPERTY(Category = BlockMaterials, VisibleAnywhere)
		class UMaterialInstance* ConnectMaterial;

	UPROPERTY(VisibleAnywhere)
		TArray<AFunctionConnector*> ValidConnections;
};
