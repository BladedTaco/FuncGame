// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionCall.h"


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

#include "Algo/AllOf.h"
#include "Kismet/GameplayStatics.h"

#include "AssetLoader_gen.h"

ABlockFunctionCall::ABlockFunctionCall() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Call.Get());
}

void ABlockFunctionCall::SetFunctionTypes() {
	FunctionName = FString(TEXT("Call"));


	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A, B };


	Inputs = {
		{ "Function", UTypeConst::New(ETypeData::FUNC, { UTypePtr::New(A), UTypePtr::New(B) }) },
		{ "Input", UTypePtr::New(A) }
	};

	Outputs = {
		{"Result", UTypePtr::New(B) }
	};

}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionCall::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		auto [v0, v1] = Destruct<2, TArray, VStar>(values);

		ArrV f = v0.ResolveToUnsafe<ArrV>();

		VStar result = f(v1);

		return { result };

	});
}
