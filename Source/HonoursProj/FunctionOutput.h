// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FunctionConnector.h"
#include "FunctionOutput.generated.h"


UCLASS()
class HONOURSPROJ_API AFunctionOutput : public AFunctionConnector
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	TArray<class AFunctionInput*> connectedTo;

	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual VStar GetValue_Impl() override;
	virtual UType* ResolveType_Impl() override;
};
