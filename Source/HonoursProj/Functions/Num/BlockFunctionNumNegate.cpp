// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionNumNegate.h"
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

ABlockFunctionNumNegate::ABlockFunctionNumNegate() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Minus.Get());
}

void ABlockFunctionNumNegate::SetFunctionTypes() {

	FunctionName = FString(TEXT("Negate"));


	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::NUM);
	TypeVars = { A };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(A) }
	};
	Outputs = {
		{"-A",  UTypePtr::New(A)  }
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionNumNegate::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		const INum* const num = t0.getTypeclass()->Num;

		VStar result = num->negate()(t0);

		return { result };

	} );
}
