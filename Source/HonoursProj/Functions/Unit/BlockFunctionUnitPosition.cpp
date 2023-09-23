// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPosition.h"

#include "Types/Dataclass/BaseTypes.h"

ABlockFunctionUnitPosition::ABlockFunctionUnitPosition() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Position.Get());
}

void ABlockFunctionUnitPosition::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get Position"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"X",  UTypeConst::New(ETypeBase::INT) },
		{"Y",  UTypeConst::New(ETypeBase::INT) }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPosition::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		FVector2D PositionVec = IsValid(Unit) ? Unit->Position : FVector2D(-1);

		VStar XOut = VStar(Int(PositionVec.X));
		VStar YOut = VStar(Int(PositionVec.Y));

		return { XOut, YOut };

	});
}
