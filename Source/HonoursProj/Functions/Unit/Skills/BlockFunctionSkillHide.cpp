// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/Skills/BlockFunctionSkillHide.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"

ABlockFunctionSkillHide::ABlockFunctionSkillHide() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Position.Get());
	FunctionIcon->SetMaterial(0, Assets()->Material.Shiny.Get());
}

void ABlockFunctionSkillHide::SetFunctionTypes() {

	FunctionName = FString(TEXT("Skill: Hide"));

	// Set Inputs and Outputs
	Inputs = {
		{"Use", UTypeConst::New(ETypeBase::BOOL)  }
	};
	Outputs = {};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionSkillHide::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		if (IsValid(Unit)) {
			auto [t0] = Destruct<1, TArray, VStar>(values);

			Unit->bOnBoard = t0.ResolveToUnsafe<Bool>().get() && TrySkill();
		}

		return { };

	});
}
