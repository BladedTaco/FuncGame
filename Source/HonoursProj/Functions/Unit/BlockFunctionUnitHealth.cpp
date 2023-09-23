// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitHealth.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Level/StatusBar.h"

ABlockFunctionUnitHealth::ABlockFunctionUnitHealth() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Health.Get());
}

void ABlockFunctionUnitHealth::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get Health"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Current",  UTypeConst::New(ETypeBase::INT) },
		{"Maximum",  UTypeConst::New(ETypeBase::INT) }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitHealth::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		int MaxVal, CurrVal = -1;

		VStar CurrentOut;
		VStar MaxOut;

		if (IsValid(Unit)) {
			CurrVal = Unit->Health->CurrentValue;
			MaxVal = Unit->Health->MaxValue;
		}

		CurrentOut = VStar(Int(CurrVal));
		MaxOut = VStar(Int(MaxVal));

		return { CurrentOut, MaxOut };

	});
}
