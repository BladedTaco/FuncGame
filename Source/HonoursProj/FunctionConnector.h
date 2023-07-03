// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"
#include "BlockFunction.h"

#include "FunctionConnector.generated.h"


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API AFunctionConnector : public AHonoursProjBlock {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFunctionConnector();

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;


	UPROPERTY(Category = Connector, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ConnectMesh;

	FTransform Connect(FVector a, FVector b);

	void Tick(float DeltaSeconds);

	virtual UType* ResolveType() PURE_VIRTUAL(AFunctionConnector::ResolveType, return NULL;);
	virtual ValType GetValue() PURE_VIRTUAL(AFunctionConnector::GetValue, return MakeTuple((UType*)NULL, (void*)NULL););

public:
	UPROPERTY(VisibleAnywhere)
		FParameter ParameterInfo;
	UPROPERTY(VisibleAnywhere)
		int Index;

	/** Pointer to Yellow material used on Connectable Connectors */
	UPROPERTY()

		class UMaterialInstance* ConnectMaterial;
	UPROPERTY()
		TArray<AFunctionConnector*> ValidConnections;
};
