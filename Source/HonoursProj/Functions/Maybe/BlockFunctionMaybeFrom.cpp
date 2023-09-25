// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMaybeFrom.h"

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

ABlockFunctionMaybeFrom::ABlockFunctionMaybeFrom() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Maybe.Get());
}

void ABlockFunctionMaybeFrom::SetFunctionTypes() {

	FunctionName = FString(TEXT("From Maybe"));



	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A };


	// Set Inputs and Outputs
	Inputs = {
		{ "Maybe",  UTypeConst::New(ETypeData::MAYBE, { UTypePtr::New(A) }) },
		{ "Fallback",  UTypePtr::New(A) }
	};
	Outputs = {
		{ "Value",  UTypePtr::New(A) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionMaybeFrom::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		VStar result = t0.ResolveToUnsafe<MaybeV>().fromMaybe(t1);

		return { result };
	} );
}
