// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/Skills/BlockFunctionSkillPositionMaybeSet.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"


ABlockFunctionSkillPositionMaybeSet::ABlockFunctionSkillPositionMaybeSet() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Position.Get());
}

void ABlockFunctionSkillPositionMaybeSet::SetFunctionTypes() {

	FunctionName = FString(TEXT("Set Position"));

	// Set Inputs and Outputs
	Inputs = {
		{"X",  UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeBase::INT) })  },
		{"Y",  UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeBase::INT) })  }
	};
	Outputs = {};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionSkillPositionMaybeSet::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		if (IsValid(Unit)) {
			auto [t0, t1] = Destruct<2, TArray, VStar>(values);

			MaybeV m0 = t0.ResolveToUnsafe<MaybeV>();
			MaybeV m1 = t1.ResolveToUnsafe<MaybeV>();

			int X = m0.fromMaybe(Int(-1)).get();
			int Y = m1.fromMaybe(Int(-1)).get();

			if ((X == -1 || Y == -1)) {
				//Unit->Position = FVector2D(-1);
				Unit->bOnBoard = !TrySkill();
				Unit->TrySetPosition(Unit->Position.X, Unit->Position.Y);
			} else {
				//Unit->Position = FVector2D(X, Y);
				Unit->bOnBoard = true;
				Unit->TrySetPosition(X, Y);
			}

		}

		return { };

	});
}
