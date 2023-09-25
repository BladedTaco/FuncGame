// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionOrdMaxMaybe.h"

#include "Types/Dataclass/Maybe_gen.h"

// Set Function Icon Mesh
ABlockFunctionOrdMaxMaybe::ABlockFunctionOrdMaxMaybe() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Ordinal.Get());
	FunctionIcon->SetMaterial(0, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(1, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(2, Assets()->Material.White.Get());
	FunctionIcon->SetMaterial(3, Assets()->Material.White.Get());
}


void ABlockFunctionOrdMaxMaybe::SetFunctionTypes() {

	FunctionName = FString(TEXT("Max"));

	
	// Initialize Type Variables
	UTypeVar* E = UTypeVar::New(ETypeClass::ORDINAL);
	TypeVars = { E };

	// Set Inputs and Outputs
	Inputs = {
		{"A", UTypePtr::New(E) },
		{"F B", UTypeConst::New(ETypeData::MAYBE, { UTypePtr::New(E) }) },
	};
	Outputs = {
		{"Max(A,B?)", UTypePtr::New(E) } 
	};
}



Arr<VStarArray, VStarArrayReturn> ABlockFunctionOrdMaxMaybe::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {
		// Destruct Values
		auto [t0, t1] = Destruct<2, TArray, VStar>(values);

		const IOrdinal* const ordinal = t0.getTypeclass()->Ordinal;

		VStar m1 = t1.ResolveToUnsafe<MaybeV>().fromMaybe(t0);
		VStar result = ordinal->max()(t0)(m1);

		return { result };
	} );
}


