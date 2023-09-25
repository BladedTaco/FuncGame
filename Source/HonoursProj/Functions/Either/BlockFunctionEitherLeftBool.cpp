// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherLeftBool.h"

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

ABlockFunctionEitherLeftBool::ABlockFunctionEitherLeftBool() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEitherLeftBool::SetFunctionTypes() {

	FunctionName = FString(TEXT("Either Left Bool"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A };

	// Set Inputs and Outputs
	Inputs = {
		{ "Right",  UTypePtr::New(A) },
		{ "IsRight", UTypeConst::New(ETypeBase::BOOL) },
	};
	Outputs = {
		{"Right | False", UTypeConst::New(ETypeData::EITHER, {
			UTypeConst::New(ETypeBase::BOOL),
			UTypePtr::New(A)
		})  }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherLeftBool::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		VStar result;

		if (t1.ResolveToUnsafe<Bool>().get()) {
			result = VStar( EitherV::AsRight(t0) );
		} else {
			result = VStar( EitherV::AsLeft(Bool(false)) );
		}

		return { result };
	} );
}
