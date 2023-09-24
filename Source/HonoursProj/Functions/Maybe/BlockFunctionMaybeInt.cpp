// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMaybeInt.h"

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

ABlockFunctionMaybeInt::ABlockFunctionMaybeInt() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Maybe.Get());
}

void ABlockFunctionMaybeInt::SetFunctionTypes() {

	FunctionName = FString(TEXT("Maybe Int Constructor"));



	// Initialize Type Variables
	TypeVars = { };


	// Set Inputs and Outputs
	Inputs = {
		{ "Is Just", UTypeConst::New(ETypeBase::BOOL) }
	};
	Outputs = {
		{ "Maybe Int",  UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeBase::INT) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionMaybeInt::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result;

		if (t0.ResolveToUnsafe<Bool>().get()) {
			result = VStar( MaybeV::Just(Int(Value)) );
		} else {
			result = VStar( MaybeV::Nothing() );
		}


		return { result };
	} );
}
