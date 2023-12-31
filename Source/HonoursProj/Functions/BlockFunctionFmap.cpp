// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionFmap.h"
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

ABlockFunctionFmap::ABlockFunctionFmap() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Functor.Get());
}

void ABlockFunctionFmap::SetFunctionTypes() {

	FunctionName = FString(TEXT("FMap"));


	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::FUNCTOR);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B };


	// Set Inputs and Outputs
	Inputs = {
		{"Func", UTypeConst::New(ETypeData::FUNC, { UTypePtr::New(A), UTypePtr::New(B) })},
		{"Over", UTypePtr::New(F, { UTypePtr::New(A) })}
	};
	Outputs = {
		{"Out",  UTypePtr::New(F, { UTypePtr::New(B) })}
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionFmap::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);
		const IFunctor* const functor = t1.getTypeclass()->Functor;

		VStar result = functor->fmap()(t0)(t1);


		return { result };

	} );
}
