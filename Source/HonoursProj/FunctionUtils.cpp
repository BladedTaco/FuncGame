// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionUtils.h"

#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
//
//#include "Components/StaticMeshComponent.h"
//#include "Engine/StaticMesh.h"
//#include "Materials/MaterialInstance.h"
//#include "Materials/Material.h"


#include "AssetLoader_gen.h"

UTypeHandler::UTypeHandler() {
	UDataTable* types = Assets.Data.TypesTable.Get();

	/*
	Maybe

	Name = Maybe
	Icon = question mark
	Colour = yellow

	Templates = T ?

	Constructors = Nothing, Just T

	Eq
	Ord
	Generic
	Monad
	Functor
	Applicative
	Traversable
	Foldable



	

	Needed for example

	Number
	Ord
	Maybe
	Position
	Bool
	Error / Kill / Damage (A type that you dont want executed)

	Functor
	Applicative
	Monad

	Semigroup
	Monoid
	Generic

	*/

}