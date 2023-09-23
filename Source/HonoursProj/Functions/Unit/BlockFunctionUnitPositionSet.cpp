// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPositionSet.h"

#include "Types/Dataclass/BaseTypes.h"

ABlockFunctionUnitPositionSet::ABlockFunctionUnitPositionSet() {
	
}

void ABlockFunctionUnitPositionSet::SetFunctionTypes() {

	FunctionName = FString(TEXT("Set Position"));

	// Set Inputs and Outputs
	Inputs = {
		{"X",  UTypeConst::New(ETypeBase::INT) },
		{"Y",  UTypeConst::New(ETypeBase::INT) }
	};
	Outputs = {};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPositionSet::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		if (IsValid(Unit)) {
			auto [t0, t1] = Destruct<2, TArray, VStar>(values);

			Unit->Position = FVector2D(t0.ResolveToUnsafe<Int>().get(), t1.ResolveToUnsafe<Int>().get());
		}

		return { };

	});
}
