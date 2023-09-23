// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitMana.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Level/StatusBar.h"

ABlockFunctionUnitMana::ABlockFunctionUnitMana() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Mana.Get());
}

void ABlockFunctionUnitMana::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get Mana"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Current",  UTypeConst::New(ETypeBase::INT) },
		{"Maximum",  UTypeConst::New(ETypeBase::INT) }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitMana::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		int MaxVal, CurrVal = -1;

		VStar CurrentOut;
		VStar MaxOut;

		if (IsValid(Unit)) {
			CurrVal = Unit->Mana->CurrentValue;
			MaxVal = Unit->Mana->MaxValue;
		}

		CurrentOut = VStar(Int(CurrVal));
		MaxOut = VStar(Int(MaxVal));

		return { CurrentOut, MaxOut };

	});
}
