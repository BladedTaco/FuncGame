// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionOrdMin.h"


// Set Function Icon Mesh
ABlockFunctionOrdMin::ABlockFunctionOrdMin() {
	FunctionIcon->SetMaterial(0, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(1, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(2, Assets()->Material.DarkGrey.Get());
	FunctionIcon->SetMaterial(3, Assets()->Material.DarkGrey.Get());
}


void ABlockFunctionOrdMin::SetFunctionTypes() {

	FunctionName = FString(TEXT("Min"));

	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::ORDINAL);
	TypeVars = { F };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(F) },
		{"B", UTypePtr::New(F) },
	};
	Outputs = {
		{"Min(A,B)", UTypePtr::New(F) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionOrdMin::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		const IOrdinal* const ordinal = t0.getTypeclass()->Ordinal;

		VStar result = ordinal->min()(t0)(t1);

		return { result };
	} );
}


