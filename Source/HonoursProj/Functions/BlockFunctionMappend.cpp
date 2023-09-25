// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMappend.h"
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

ABlockFunctionMappend::ABlockFunctionMappend() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Chain.Get());
}

void ABlockFunctionMappend::SetFunctionTypes() {

	FunctionName = FString(TEXT("Mappend"));


	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::SEMIGROUP);
	TypeVars = { F };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(F) },
		{"B", UTypePtr::New(F) }
	};
	Outputs = {
		{"First Right",  UTypePtr::New(F) }
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionMappend::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		VStar result = t0.getTypeclass()->Semigroup->mappend()(t0)(t1);

		return { result };

	} );
}
