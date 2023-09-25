// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPositionMoveLR.h"

#include "Types/Dataclass/BaseTypes.h"

ABlockFunctionUnitPositionMoveLR::ABlockFunctionUnitPositionMoveLR() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Position.Get());
}

void ABlockFunctionUnitPositionMoveLR::SetFunctionTypes() {

	FunctionName = FString(TEXT("Move Left Right"));

	// Set Inputs and Outputs
	Inputs = {
		{"dX",  UTypeConst::New(ETypeBase::INT) }
	};
	Outputs = {};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPositionMoveLR::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {



		// Destruct Values
		auto [t0] = Destruct<1, TArray, VStar>(values);

		int dx = t0.ResolveToUnsafe<Int>().get();

		if (IsValid(Unit)) {
			Unit->TrySetPosition(Unit->Position.X + dx, Unit->Position.Y);
		}

		return { };

	});
}
