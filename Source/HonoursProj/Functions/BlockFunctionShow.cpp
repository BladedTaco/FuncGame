#include "BlockFunctionShow.h"


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



void ABlockFunctionShow::SetFunctionTypes() {

	FunctionName = FString(TEXT("Show"));


	//UTypeVar* A = UTypeVar::New(ETypeClass::SHOW);
	//TypeVars = { A };
	UTypeVar* A = UTypeVar::New(ETypeClass::SHOW);
	TypeVars = { A };


	Inputs = {
		{"Showable", UTypePtr::New(A) }
	};

	Outputs = {
		{"Passthrough", UTypePtr::New(A) }
	};

}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionShow::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {


		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		// Show
		const IShow* const show = t0.getTypeclass()->Show;
		this->HUD.Inst()->LastResult = show->show()(t0);

		// Return empty
		return { t0 };

	});
}
