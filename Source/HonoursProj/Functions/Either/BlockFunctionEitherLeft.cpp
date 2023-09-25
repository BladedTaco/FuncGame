// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherLeft.h"

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
#include "Types/Dataclass/Either_gen.h"



#include "MyUtils.h"
#include "AssetLoader_gen.h"

ABlockFunctionEitherLeft::ABlockFunctionEitherLeft() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEitherLeft::SetFunctionTypes() {

	FunctionName = FString(TEXT("EitherLeft Constructor"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{ "Left",  UTypePtr::New(A) }
	};
	Outputs = {
		{ "EitherLeft Value",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(A) , UTypePtr::New(B) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherLeft::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result = VStar( EitherV::AsLeft(t0) );

		return { result };
	} );
}
