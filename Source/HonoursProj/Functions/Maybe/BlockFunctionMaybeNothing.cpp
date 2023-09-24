// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionMaybeNothing.h"

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "HUD/FunctionHUD.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Dataclass/BaseTypes.h"
#include "Types/Dataclass/Maybe_gen.h"


#include "MyUtils.h"
#include "AssetLoader_gen.h"

ABlockFunctionMaybeNothing::ABlockFunctionMaybeNothing() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Maybe.Get());
}

void ABlockFunctionMaybeNothing::SetFunctionTypes() {

	FunctionName = FString(TEXT("Nothing Constructor"));



	// Initialize Type Variables
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { A };


	// Set Inputs and Outputs
	Inputs = {};
	Outputs = {
		{ "Nothing",  UTypeConst::New(ETypeData::MAYBE, { UTypePtr::New(A) }) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionMaybeNothing::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		return { VStar( MaybeV::Nothing() ) };
	} );
}
