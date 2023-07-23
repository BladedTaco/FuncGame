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

#include "HUD/FunctionHUD.h"


#include "MyUtils.h"



void ABlockFunctionConstant::SetFunctionTypes() {

	FunctionName = FString(TEXT("Number Constant"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Out",  UTypeConst::New(ETypeData::NUMBER, {UTypeConst::New(ETypeBase::INT)})}
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionConstant::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar out = VStar(NumberV(Value));

		//this->TextComponent->SetText(FText::Format(FText::FromString(FString("Val {0}")), this->Value));

		this->HUD.Instance->LastResult = FString::Format(TEXT("Val {0}"), { this->Value });

		return { out };

		//return {};
		////Number<int> n(Value);


		//this->TextComponent->SetText(FText::Format(FText::FromString(FString("Val {0}")), this->Value));

		//VStar val(Value); // Int
		//NumberV n(val);		// NumberV
		//VStar res(Outputs[0].Type, n); // VStar

		//VStarArray out = {std::move(res)};

		//return std::move(out);
	});
}
