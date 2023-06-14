// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"
#include "FunctionConnector.generated.h"

USTRUCT(BlueprintType)
struct FFuncConnector {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		FString Type;
};


/**
 * 
 */
UCLASS()
class HONOURSPROJ_API AFunctionConnector : public AHonoursProjBlock {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFunctionConnector();

	virtual void HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual void HandleRClick(UPrimitiveComponent* ClickedComponent) override;

	UPROPERTY(VisibleAnywhere)
	AFunctionConnector* connectedTo;

	UPROPERTY(Category = Connector, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ConnectMesh;

	FTransform Connect(FVector a, FVector b);

	void Tick(float DeltaSeconds);
};
