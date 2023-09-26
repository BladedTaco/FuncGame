// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionFoldR.h"
#include "Engine/World.h"


#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Typeclass/Functor.h"
#include "Types/Typeclass/Foldable.h"
#include "Types/Typeclass/Show.h"
#include "Types/Dataclass/Maybe_gen.h"
#include "Types/Dataclass/BaseTypes.h"

#include "MyUtils.h"


#include "HUD/FunctionHUD.h"

ABlockFunctionFoldR::ABlockFunctionFoldR() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Foldable.Get());
}

void ABlockFunctionFoldR::SetFunctionTypes() {

	FunctionName = FString(TEXT("Fold R"));


	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::FUNCTOR);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B };


	// Set Inputs and Outputs
	Inputs = {
		{"Func", UTypeConst::New(ETypeData::FUNC, {
			 UTypePtr::New(A),
			 UTypeConst::New(ETypeData::FUNC, {
				UTypePtr::New(B),
				UTypePtr::New(B) 
			})
		})},
		{"Initial", UTypePtr::New(B) },
		{"Foldable", UTypePtr::New(F, { UTypePtr::New(A) })}
	};
	Outputs = {
		{"Out",  UTypePtr::New(B) }
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionFoldR::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0, t1, t2] = Destruct<3, TArray, VStar>(values);

		VStar result = t2.getTypeclass()->Foldable->foldr()(t0)(t1)(t2);

		return { result };

	} );
}
