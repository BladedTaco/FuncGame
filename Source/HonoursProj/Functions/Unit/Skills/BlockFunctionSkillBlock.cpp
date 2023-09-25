// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/Skills/BlockFunctionSkillBlock.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"

ABlockFunctionSkillBlock::ABlockFunctionSkillBlock() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Shield.Get());
}

void ABlockFunctionSkillBlock::SetFunctionTypes() {

	FunctionName = FString(TEXT("Skill: Block"));

	// Set Inputs and Outputs
	Inputs = {
		{"Use", UTypeConst::New(ETypeBase::BOOL)  }
	};
	Outputs = {};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionSkillBlock::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		if (IsValid(Unit) && IsValid(Shield)) {
			auto [t0] = Destruct<1, TArray, VStar>(values);

			Shield->bOnBoard = t0.ResolveToUnsafe<Bool>().get() && TrySkill();

			FVector2D ShieldPos = Unit->Position + ShieldFacing;
			Shield->TrySetPosition(ShieldPos.X, ShieldPos.Y);
		}

		return { };

	});
}
