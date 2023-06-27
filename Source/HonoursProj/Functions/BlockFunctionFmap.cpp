// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionFmap.h"

ABlockFunctionFmap::ABlockFunctionFmap() {
	// Initialize Templates
	FTypeInfo A = { ETypeBase::TEMPLATE };
	FTypeInfo B = { ETypeBase::TEMPLATE };
	FTypeInfo F = { EType::FUNCTOR, { {&A} }};

	BaseType.Templates = { F, A, B };

	BaseType.Inputs = { 
		{"Func", {EType::ARROW, {{&A}, {&B}} }},
		{"Over", F}
	};
	BaseType.Outputs = {
		{"Out", {&F, {{&B}} }}
	};

	// DeepCopy BaseType to CurrentType
	CurrentType = { BaseType };

}

void ABlockFunctionFmap::BeginPlay() {

}

void* ABlockFunctionFmap::GetValue() {
	return NULL;
}

FFunctionInfo ResolveType() {
	return FFunctionInfo();
}