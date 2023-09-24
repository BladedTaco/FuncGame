// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionLiftA2.h"
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

ABlockFunctionLiftA2::ABlockFunctionLiftA2() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.LiftA2.Get());
}

void ABlockFunctionLiftA2::SetFunctionTypes() {

	FunctionName = FString(TEXT("LiftA2"));


	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::APPLICATIVE);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* C = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B, C };


	// Set Inputs and Outputs
	Inputs = {
		{"Ternary", UTypeConst::New(ETypeData::FUNC, { 
			UTypePtr::New(A), 
			UTypeConst::New(ETypeData::FUNC, { 
				UTypePtr::New(B), 
				UTypePtr::New(C) 
			})
		})},
		{"F A", UTypePtr::New(F, { UTypePtr::New(A) })},
		{"F B", UTypePtr::New(F, { UTypePtr::New(B) })},
	};
	Outputs = {
		{"F C", UTypePtr::New(F, { UTypePtr::New(C) })}
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionLiftA2::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0, t1, t2] = Destruct<3, TArray, VStar>(values);
		const IApplicative* const applic = t1.getTypeclass()->Applicative;

		VStar result = applic->liftA2()(t0)(t1)(t2);

		return { result };

	} );
}
