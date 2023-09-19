// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPosition.h"

#include "Types/Int_gen.h"

void ABlockFunctionUnitPosition::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get Position"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"X", UTypeConst::New(ETypeData::NUMBER, { UTypeConst::New(ETypeBase::INT) }) },
		{"Y", UTypeConst::New(ETypeData::NUMBER, { UTypeConst::New(ETypeBase::INT) }) }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPosition::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		FVector2D PositionVec = IsValid(Unit) ? Unit->Position : FVector2D(-1);

		VStar XOut = VStar(NumberV(PositionVec.X));
		VStar YOut = VStar(NumberV(PositionVec.Y));

		return { XOut, YOut };

	});
}
