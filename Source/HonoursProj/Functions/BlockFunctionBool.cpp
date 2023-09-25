// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionBool.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Dataclass/BaseTypes.h"

#include "HUD/FunctionHUD.h"


#include "MyUtils.h"

#include "AssetLoader_gen.h"


// Set Function Icon Mesh
ABlockFunctionBool::ABlockFunctionBool() {
	FunctionIcon->SetStaticMesh(Assets()->TypeIcon.Bool.Get());
}

void ABlockFunctionBool::SetFunctionTypes() {

	FunctionName = FString(TEXT("Bool"));

	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{"Out", UTypeConst::New(ETypeBase::BOOL) }
	};
}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionBool::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar out = VStar(Bool(Value));

		return { out };
	});
}
