// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionOrdEQMaybe.h"


// Set Function Icon Mesh
ABlockFunctionOrdEQMaybe::ABlockFunctionOrdEQMaybe() {
	FunctionIcon->SetMaterial(0, Assets()->Material.DarkGrey.Get());
	FunctionIcon->SetMaterial(1, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(2, Assets()->Material.DarkGrey.Get());
}


void ABlockFunctionOrdEQMaybe::SetFunctionTypes() {

	FunctionName = FString(TEXT("Equal To"));

	// Initialize Type Variables
	UTypeVar* E = UTypeVar::New(ETypeClass::EQ);
	UTypeVar* F = UTypeVar::New(ETypeClass::FUNCTOR);
	TypeVars = { F, E };

	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(E) },
		{"F B", UTypePtr::New(F, { UTypePtr::New(E) }) },
	};
	Outputs = {
		{"F (A == B)",  UTypePtr::New(F, {UTypeConst::New(ETypeBase::BOOL)} )} 
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionOrdEQMaybe::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		const IEq* const eq = t0.getTypeclass()->Eq;

		// MaybeV m = t1.ResolveToUnsafe<MaybeV>();

		ArrV eqV = eq->eq()(t0).ToArrV();

		VStar result = t1.getTypeclass()->Functor->fmap()(eqV)(t1);

		// Bool result = (t1);

		return { result };
	} );
}


