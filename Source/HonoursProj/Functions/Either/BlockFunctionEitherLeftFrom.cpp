// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherLeftFrom.h"

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

ABlockFunctionEitherLeftFrom::ABlockFunctionEitherLeftFrom() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEitherLeftFrom::SetFunctionTypes() {

	FunctionName = FString(TEXT("Either From Left"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{ "Either",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(A) , UTypePtr::New(B) }) },
		{ "Fallback",  UTypePtr::New(A) }
	};
	Outputs = {
		{ "Left",  UTypePtr::New(A) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherLeftFrom::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		VStar result = t0.ResolveToUnsafe<EitherV>().fromLeft(t1);

		return { result };
	} );
}
