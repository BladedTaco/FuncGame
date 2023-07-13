#include "BlockFunctionShow.h"


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


#include "FunctionHUD.h"



void ABlockFunctionShow::SetFunctionTypes() {

	HUDInstance->FunctionName = FString(TEXT("Show"));

	HUDInstance->LastResult = FString(TEXT("Unevaluated"));

	UTypeVar* A = UTypeVar::New(ETypeClass::SHOW);
	TypeVars = { A };

	Inputs = {
		{"Showable", UTypePtr::New(A) }
	};

}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionShow::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		// Show
		const IShow* const show = t0.getTypeclass()->Show;
		this->HUDInstance->LastResult = show->show()(t0);

		// Return empty
		return { };

	});
}