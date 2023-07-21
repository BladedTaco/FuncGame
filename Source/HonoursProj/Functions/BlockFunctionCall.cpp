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

#include "Types/Functor.h"
#include "Types/Show.h"
#include "Types/Maybe_gen.h"
#include "Types/Func_gen.h"
#include "Types/Int_gen.h"

#include "MyUtils.h"


#include "HUD/FunctionHUD.h"
#include "BlockFunctionCounter.h"

#include "Algo/AllOf.h"
#include "Kismet/GameplayStatics.h"


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

		ArrV f = v0.GetUnsafe<ArrV>();

		VStar result = f(v1);

		// Show
		const IShow* const show = result.getTypeclass()->Show;
		this->HUDInstance->LastResult = show->show()(result);

		return { result };

	});
}
