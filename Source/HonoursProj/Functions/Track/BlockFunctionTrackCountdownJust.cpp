// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Track/BlockFunctionTrackCountdownJust.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"

ABlockFunctionTrackCountdownJust::ABlockFunctionTrackCountdownJust() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Counter.Get());
}

void ABlockFunctionTrackCountdownJust::SetFunctionTypes() {

	FunctionName = FString(TEXT("Just Countdown"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Just Remaining",  UTypeConst::New(ETypeData::MAYBE, {UTypeConst::New(ETypeBase::INT) }) },
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionTrackCountdownJust::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar Out = VStar(MaybeV::Just(Int(Countdown)));

		return { Out };

	});
}
