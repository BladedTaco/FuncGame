// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionApply.h"
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

ABlockFunctionApply::ABlockFunctionApply() {

}

void ABlockFunctionApply::SetFunctionTypes() {

	FunctionName = FString(TEXT("Apply"));


	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::APPLICATIVE);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B };


	// Set Inputs and Outputs
	Inputs = {
		{"F Function", UTypePtr::New(F, { 
			UTypeConst::New(ETypeData::FUNC, { 
				UTypePtr::New(A), 
				UTypePtr::New(B) 
			})
		})},
		{"F A", UTypePtr::New(F, { UTypePtr::New(A) })},
	};
	Outputs = {
		{"F B", UTypePtr::New(F, { UTypePtr::New(B) })}
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionApply::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);
		const IApplicative* const applic = t1.getTypeclass()->Applicative;

		VStar result = applic->apply()(t0)(t1);

		return { result };

	} );
}
