// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionBind.h"
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

ABlockFunctionBind::ABlockFunctionBind() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Monad.Get());
}

void ABlockFunctionBind::SetFunctionTypes() {

	FunctionName = FString(TEXT("Bind"));


	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::MONAD);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B };


	// Set Inputs and Outputs
	Inputs = {
		{"Monad", UTypePtr::New(F, { UTypePtr::New(A) })},
		{"Effect", UTypeConst::New(ETypeData::FUNC, {
			UTypePtr::New(A), 
			UTypePtr::New(F, { UTypePtr::New(B) }) 
		})}
	};
	Outputs = {
		{"Effected Monad",  UTypePtr::New(F, { UTypePtr::New(B) })}
	};
}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionBind::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);
		
		VStar result = t0.getTypeclass()->Monad->bind()(t0)(t1);


		return { result };

	} );
}
