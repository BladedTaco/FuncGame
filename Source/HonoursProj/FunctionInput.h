// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FunctionConnector.h"
#include "FunctionInput.generated.h"


UCLASS()
class HONOURSPROJ_API AFunctionInput : public AFunctionConnector
{
	GENERATED_BODY()

public:
	void Tick(float DeltaSeconds);

	UPROPERTY(VisibleAnywhere)
	class AFunctionOutput* connectedTo;

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual ValType GetValue() override;
	virtual UType* ResolveType() override;
};
