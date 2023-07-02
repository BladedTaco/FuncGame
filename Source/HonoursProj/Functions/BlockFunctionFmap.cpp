// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionFmap.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"



#include "MyUtils.h"





ABlockFunctionFmap::ABlockFunctionFmap() {
	// Initialize Type Variables
	UTypeVar* F = UTypeVar::New(ETypeClass::FUNCTOR);
	UTypeVar* A = UTypeVar::New(ETypeClass::ANY);
	UTypeVar* B = UTypeVar::New(ETypeClass::ANY);
	TypeVars = { F, A, B };


	// Set Inputs and Outputs
	Inputs = { 
		{"Func", UTypeConst::New(ETypeData::FUNC, { UTypePtr::New(A), UTypePtr::New(B) } )},
		{"Over", UTypePtr::New(F, { UTypePtr::New(A) } )}
	};
	Outputs = {
		{"Out",  UTypePtr::New(F, { UTypePtr::New(B) })}
	};

}
