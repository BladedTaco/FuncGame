// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/Skills/BlockFunctionSkillBlockEither.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"
#include "Types/Dataclass/Either_gen.h"



ABlockFunctionSkillBlockEither::ABlockFunctionSkillBlockEither() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Shield.Get());
}

void ABlockFunctionSkillBlockEither::SetFunctionTypes() {

	FunctionName = FString(TEXT("Skill: Block/Move"));

	// Set Inputs and Outputs
	Inputs = {
		{"Use | dX", UTypeConst::New(ETypeData::EITHER, {
			UTypeConst::New(ETypeBase::BOOL),
			UTypeConst::New(ETypeBase::INT),
		})  }
	};
	Outputs = {};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionSkillBlockEither::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		if (IsValid(Unit) && IsValid(Shield)) {
			auto [t0] = Destruct<1, TArray, VStar>(values);

			EitherV e0 = t0.ResolveToUnsafe<EitherV>();

			// Block // Bool
			bool block = e0.fromLeft(Bool(false)).get();
			Shield->bOnBoard = block && TrySkill();
			FVector2D ShieldPos = Unit->Position + ShieldFacing;
			Shield->TrySetPosition(ShieldPos.X, ShieldPos.Y);

			// Move dX // Int
			int dx = e0.fromRight(Int(0)).get();
			if (dx == FMath::Sign(dx)) {
				Unit->TrySetPosition(Unit->Position.X + dx, Unit->Position.Y);
			}
		}

		return { };
	});
}
