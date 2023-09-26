// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionConst.h"
#include "Engine/World.h"


#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Typeclass/Functor.h"
#include "Types/Typeclass/Show.h"
#include "Types/Dataclass/Maybe_gen.h"
#include "Types/Dataclass/BaseTypes.h"

#include "MyUtils.h"


#include "HUD/FunctionHUD.h"

ABlockFunctionConst::ABlockFunctionConst() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Key.Get());
}

void ABlockFunctionConst::SetFunctionTypes() {

	FunctionName = FString(TEXT("Const"));


	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(A) },
		{"B", UTypePtr::New(B) },
	};
	Outputs = {
		{"A",  UTypePtr::New(A) }
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionConst::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		VStar out = PreludeV::constant(t0)(t1);

		return { out };

	} );
}
