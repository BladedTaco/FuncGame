// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPositionLRDist.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Either_gen.h"

ABlockFunctionUnitPositionLRDist::ABlockFunctionUnitPositionLRDist() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Position.Get());
}

void ABlockFunctionUnitPositionLRDist::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get LR or Distance"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"LR | Distance",  UTypeConst::New(ETypeData::EITHER, {
			UTypeConst::New(ETypeBase::BOOL),
			UTypeConst::New(ETypeBase::INT),
		})}
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPositionLRDist::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Error State
		if (!IsValid(Unit) || !IsValid(RelativeTo)) return { VStar(EitherV::AsLeft(Bool(false))) };

		FVector2D dVec = Unit->Position - RelativeTo->Position;

		VStar result;

		if (dVec.X == 0) {
			result = VStar(EitherV::AsRight(Int(dVec.Y)));
		} else {
			result = VStar(EitherV::AsLeft(Bool(dVec.X > 0)));
		}

		return { result };

	});
}
