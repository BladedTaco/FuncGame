// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionOrdMax.h"


// Set Function Icon Mesh
ABlockFunctionOrdMax::ABlockFunctionOrdMax() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Ordinal.Get());
	FunctionIcon->SetMaterial(0, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(1, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(2, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(3, Assets()->Material.White.Get());
}


void ABlockFunctionOrdMax::SetFunctionTypes() {

	FunctionName = FString(TEXT("Max"));

	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::ORDINAL);
	TypeVars = { F };


	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(F) },
		{"B", UTypePtr::New(F) },
	};
	Outputs = {
		{"Max(A,B)", UTypePtr::New(F) }
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionOrdMax::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		const IOrdinal* const ordinal = t0.getTypeclass()->Ordinal;

		VStar result = ordinal->max()(t0)(t1);

		return { result };
	} );
}


