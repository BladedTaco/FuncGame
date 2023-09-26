// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPositionDists.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Either_gen.h"

ABlockFunctionUnitPositionDists::ABlockFunctionUnitPositionDists() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Position.Get());
}

void ABlockFunctionUnitPositionDists::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get dX or dY"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"dX | dY",  UTypeConst::New(ETypeData::EITHER, {
			UTypeConst::New(ETypeBase::INT),
			UTypeConst::New(ETypeBase::INT),
		})}
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPositionDists::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Error State
		if (!IsValid(Unit) || !IsValid(RelativeTo)) return { VStar(EitherV::AsLeft(Int(0))) };

		FVector2D dVec = Unit->Position - RelativeTo->Position;

		VStar result;

		if (dVec.X == 0) {
			result = VStar(EitherV::AsRight(Int(dVec.Y)));
		} else {
			result = VStar(EitherV::AsLeft(Int(dVec.X)));
		}

		return { result };

	});
}
