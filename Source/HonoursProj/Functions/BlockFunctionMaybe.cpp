// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMaybe.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "HUD/FunctionHUD.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Int_gen.h"
#include "Types/Maybe_gen.h"



#include "MyUtils.h"


void ABlockFunctionMaybe::SetFunctionTypes() {

	FunctionName = FString(TEXT("Maybe Constructor"));



	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A };


	// Set Inputs and Outputs
	Inputs = {
		{ "Value",  UTypePtr::New(A) }
	};
	Outputs = {
		{ "Maybe Value",  UTypeConst::New(ETypeData::MAYBE, { UTypePtr::New(A) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionMaybe::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result;

		if (this->IsNothing) {
			result = VStar( MaybeV::Nothing() );
		} else {
			result = VStar( MaybeV::Just(t0) );
		}

		const IShow* const show = result.getTypeclass()->Show;
		//this->TextComponent->SetText(FText::FromString(show->show()(result)));

		this->HUD.Inst()->LastResult = show->show()(result);

		//this->TextComponent->SetText(FText::Format(FText::FromString(FString("Type {0}")), FText::FromString(result.Type()->ToString())));

		return { result };
	} );
}
