// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunctionPull.h"
#include "BlockFunctionPullGeneral.generated.h"

/**
 * 
 */
UCLASS()
class HONOURSPROJ_API ABlockFunctionPullGeneral : public ABlockFunctionPull
{
	GENERATED_BODY()
public:

};

/*
Factory

Function = Ordinal<T>::gt<>

Inputs = T a, T b

Outputs = ORD


PP_DEFINE_FUNCTION(
	NAMESPACE
	(TEMPLATE...)
	FUNCTION
	(TEMPLATE...)
	INPUTS
	OUTPUTS
)

PP_DEFINE_FUNCTION(
	Functor
	fmap
	<>

)

*/
