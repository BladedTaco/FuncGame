// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/BlockFunctionUnitPositionMaybe.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"

ABlockFunctionUnitPositionMaybe::ABlockFunctionUnitPositionMaybe() {
	
}

void ABlockFunctionUnitPositionMaybe::SetFunctionTypes() {

	FunctionName = FString(TEXT("Get Maybe Position"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"X",  UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeBase::INT) })  },
		{"Y",  UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeBase::INT) })  }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionUnitPositionMaybe::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		FVector2D PositionVec = IsValid(Unit) ? Unit->Position : FVector2D(-1);

		VStar XOut;
		VStar YOut;

		if (PositionVec == FVector2D(-1)) {
			XOut = VStar(MaybeV::Nothing());
			YOut = VStar(MaybeV::Nothing());
		} else {
			XOut = VStar(MaybeV::Just(Int(PositionVec.X)));
			YOut = VStar(MaybeV::Just(Int(PositionVec.Y)));
		}


		return { XOut, YOut };

	});
}
