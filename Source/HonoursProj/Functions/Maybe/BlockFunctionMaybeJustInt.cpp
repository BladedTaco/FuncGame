// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMaybeJustInt.h"

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

ABlockFunctionMaybeJustInt::ABlockFunctionMaybeJustInt() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Maybe.Get());
}

void ABlockFunctionMaybeJustInt::SetFunctionTypes() {

	FunctionName = FString(TEXT("Just Int Constructor"));



	// Initialize Type Variables
	TypeVars = { };


	// Set Inputs and Outputs
	Inputs = {
	};
	Outputs = {
		{ "Just Int",  UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeBase::INT) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionMaybeJustInt::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar result = VStar( MaybeV::Just(Int(Value)) );


		return { result };
	} );
}
