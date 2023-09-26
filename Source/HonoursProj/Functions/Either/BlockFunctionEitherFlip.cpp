// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherFlip.h"

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

ABlockFunctionEitherFlip::ABlockFunctionEitherFlip() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEitherFlip::SetFunctionTypes() {

	FunctionName = FString(TEXT("Flip Either"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{ "Either Value",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(A) , UTypePtr::New(B) }) }
	};
	Outputs = {
		{ "Flipped Either",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(B) , UTypePtr::New(A) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherFlip::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result;

		EitherV e0 = t0.ResolveToUnsafe<EitherV>();

		if (e0.isLeft().get()) {
			result = VStar( EitherV::AsRight(e0.get()) );
		} else {
			result = VStar( EitherV::AsLeft(e0.get()) );
		}

		return { result };
	} );
}
