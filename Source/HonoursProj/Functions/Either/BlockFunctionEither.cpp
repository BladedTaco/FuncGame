// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEither.h"

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

ABlockFunctionEither::ABlockFunctionEither() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEither::SetFunctionTypes() {

	FunctionName = FString(TEXT("Either Constructor"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{ "Left",  UTypePtr::New(A) },
		{ "Right", UTypePtr::New(B) },
		{ "IsRight", UTypeConst::New(ETypeBase::BOOL) },
	};
	Outputs = {
		{ "Either Value",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(A) , UTypePtr::New(B) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEither::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0, t1, t2] = Destruct<3, TArray, VStar>(values);

		VStar result;

		if (t2.ResolveToUnsafe<Bool>().get()) {
			result = VStar( EitherV::AsRight(t1) );
		} else {
			result = VStar( EitherV::AsLeft(t0) );
		}

		return { result };
	} );
}
