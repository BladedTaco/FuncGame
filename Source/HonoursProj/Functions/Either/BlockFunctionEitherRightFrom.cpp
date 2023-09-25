// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionEitherRightFrom.h"

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

ABlockFunctionEitherRightFrom::ABlockFunctionEitherRightFrom() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Either.Get());
}

void ABlockFunctionEitherRightFrom::SetFunctionTypes() {

	FunctionName = FString(TEXT("Either From Right"));

	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{ "Either",  UTypeConst::New(ETypeData::EITHER, { UTypePtr::New(A) , UTypePtr::New(B) }) },
		{ "Fallback",  UTypePtr::New(B) }
	};
	Outputs = {
		{ "Right",  UTypePtr::New(B) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionEitherRightFrom::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		VStar result = t0.ResolveToUnsafe<EitherV>().fromRight(t1);

		return { result };
	} );
}
