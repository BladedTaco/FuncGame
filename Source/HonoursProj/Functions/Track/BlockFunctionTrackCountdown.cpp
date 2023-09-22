// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Track/BlockFunctionTrackCountdown.h"

#include "Types/Dataclass/BaseTypes.h"

ABlockFunctionTrackCountdown::ABlockFunctionTrackCountdown() {
	
}

void ABlockFunctionTrackCountdown::SetFunctionTypes() {

	FunctionName = FString(TEXT("Countdown"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Remaining",  UTypeConst::New(ETypeBase::INT) },
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionTrackCountdown::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar Out = VStar(Int(Countdown));

		return { Out };

	});
}
