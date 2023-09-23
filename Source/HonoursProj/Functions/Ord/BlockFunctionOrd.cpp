// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionOrd.h"


// Set Function Icon Mesh
ABlockFunctionOrd::ABlockFunctionOrd() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.OrdinalFunc.Get());
	FunctionIcon->SetMaterial(0, Assets()->Material.DarkGrey.Get());
	FunctionIcon->SetMaterial(1, Assets()->Material.DarkGrey.Get());
	FunctionIcon->SetMaterial(2, Assets()->Material.DarkGrey.Get());
}


void ABlockFunctionOrd::SetFunctionTypes() {

	FunctionName = FString(TEXT("Ordering"));



	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::ORDINAL);
	TypeVars = { F };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(F) },
		{"B", UTypePtr::New(F) },
	};
	Outputs = {
		{"A ? B", UTypeConst::New(ETypeBase::BOOL)}
	};
}



// Arr<VStarArray, VStarArrayReturn> ABlockFunctionOrd::GetInnerFunc() {
// 	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

// 		// Destruct Values
// 		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

// 		const IOrdinal* const ordinal = t0.getTypeclass()->Ordinal;

// 		Bool result = ordinal->gt()(t0)(t1);

// 		return { VStar(result) };
// 	} );
// }


