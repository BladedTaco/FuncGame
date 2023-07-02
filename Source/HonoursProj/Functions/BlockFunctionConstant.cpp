// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionConstant.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Int_gen.h"



#include "MyUtils.h"



ABlockFunctionConstant::ABlockFunctionConstant() {

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Out",  UTypeConst::New(ETypeData::NUMBER, {UTypeConst::New(ETypeBase::INT)})}
	};
}

Arr<ValArray&, TArray<void*>> ABlockFunctionConstant::GetInnerFunc() {
	return Arr<ValArray&, TArray<void*>>([this](ValArray& values) -> TArray<void*> {

		this->TextComponent->SetText(FText::Format(FText::FromString(FString("Val {0}")), this->Value));

		this->ConcreteOutputs = { this->Value };
		this->OutputValues = { ( void* )&this->ConcreteOutputs };
		return this->OutputValues;
	});
}
