// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionOrdEQ.h"


// Set Function Icon Mesh
ABlockFunctionOrdEQ::ABlockFunctionOrdEQ() {
	FunctionIcon->SetMaterial(0, Assets()->Material.DarkGrey.Get());
	FunctionIcon->SetMaterial(1, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(2, Assets()->Material.DarkGrey.Get());
}


void ABlockFunctionOrdEQ::SetFunctionTypes() {

	FunctionName = FString(TEXT("Equal To"));

	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::EQ);
	TypeVars = { F };

	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(F) },
		{"B", UTypePtr::New(F) },
	};
	Outputs = {
		{"A == B", UTypeConst::New(ETypeBase::BOOL)}
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionOrdEQ::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		const IEq* const eq = t0.getTypeclass()->Eq;

		Bool result = eq->eq()(t0)(t1);

		return { VStar(result) };
	} );
}


