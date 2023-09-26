// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherLeftBoolSign.h"

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

ABlockFunctionEitherLeftBoolSign::ABlockFunctionEitherLeftBoolSign() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Sign.Get());
}

void ABlockFunctionEitherLeftBoolSign::SetFunctionTypes() {

	FunctionName = FString(TEXT("Either Side to Sign"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A };


	// Set Inputs and Outputs
	Inputs = {
		{ "Either Side",  UTypeConst::New(ETypeData::EITHER, { 
			UTypeConst::New(ETypeBase::BOOL),
			UTypePtr::New(A) 
		}) }
	};
	Outputs = {
		{ "dX",  UTypeConst::New(ETypeBase::INT) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherLeftBoolSign::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		VStar result;

		EitherV e0 = t0.ResolveToUnsafe<EitherV>();

		if (e0.isLeft().get()) {
			result = VStar(Int(e0.get().ResolveToUnsafe<Bool>().get() ? 1 : -1));
		} else {
			result = VStar(Int(0));
		}

		return { result };
	} );
}
