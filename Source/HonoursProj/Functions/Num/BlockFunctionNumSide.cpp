// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionNumSide.h"
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

ABlockFunctionNumSide::ABlockFunctionNumSide() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Sign.Get());
}

void ABlockFunctionNumSide::SetFunctionTypes() {

	FunctionName = FString(TEXT("Sign"));


	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::NUM);
	TypeVars = { A };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(A) },
		{"B", UTypePtr::New(A) },
	};
	Outputs = {
		{"A <?> B",  UTypePtr::New(A)  }
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionNumSide::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		const INum* const num = t0.getTypeclass()->Num;

		int i0 = t0.ResolveToUnsafe<Int>().get();
		int i1 = t1.ResolveToUnsafe<Int>().get();

		VStar result = num->sign()(VStar(Int(i1 - i0)));

		return { result };

	} );
}
