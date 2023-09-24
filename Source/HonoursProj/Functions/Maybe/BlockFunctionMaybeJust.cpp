// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMaybeJust.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "HUD/FunctionHUD.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"


#include "MyUtils.h"
#include "AssetLoader_gen.h"

ABlockFunctionMaybeJust::ABlockFunctionMaybeJust() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Maybe.Get());
}

void ABlockFunctionMaybeJust::SetFunctionTypes() {

	FunctionName = FString(TEXT("Just Constructor"));



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



Arr<VStarArray, VStarArrayReturn> ABlockFunctionMaybeJust::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result;

		result = VStar( MaybeV::Just(t0) );


		return { result };
	} );
}
