// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FunctionConnector.h"
#include "FunctionInput.generated.h"

class AFunctionOutput;

UCLASS()
class HONOURSPROJ_API AFunctionInput : public AFunctionConnector
{
	GENERATED_BODY()

public:
	void Tick(float DeltaSeconds);

	UPROPERTY(VisibleAnywhere)
	AFunctionOutput* connectedTo;

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual VStar GetValue_Impl() override;
	virtual UType* ResolveType_Impl() override;



	virtual const TArray<AFunctionConnector*> GetConnections() override;
	const TArray<AFunctionOutput*> GetConnectedOutputs();
};
