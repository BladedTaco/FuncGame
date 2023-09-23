// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitStamina.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Level/StatusBar.h"

ABlockFunctionUnitStamina::ABlockFunctionUnitStamina() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Stamina.Get());
}

void ABlockFunctionUnitStamina::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get Stamina"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Current",  UTypeConst::New(ETypeBase::INT) },
		{"Maximum",  UTypeConst::New(ETypeBase::INT) }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitStamina::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		int MaxVal, CurrVal = -1;

		VStar CurrentOut;
		VStar MaxOut;

		if (IsValid(Unit)) {
			CurrVal = Unit->Stamina->CurrentValue;
			MaxVal = Unit->Stamina->MaxValue;
		}

		CurrentOut = VStar(Int(CurrVal));
		MaxOut = VStar(Int(MaxVal));

		return { CurrentOut, MaxOut };

	});
}
