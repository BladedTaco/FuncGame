// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherRight.h"

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

ABlockFunctionEitherRight::ABlockFunctionEitherRight() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEitherRight::SetFunctionTypes() {

	FunctionName = FString(TEXT("EitherRight Constructor"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{ "Right",  UTypePtr::New(B) }
	};
	Outputs = {
		{ "EitherLeft Value",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(A) , UTypePtr::New(B) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherRight::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result = VStar( EitherV::AsRight(t0) );

		return { result };
	} );
}
