// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "FunctionUtils.generated.h"


//
//UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
//enum class ETypeTraits : uint8 {
//	NONE			= 0 UMETA(Hidden)
//,	NUMBER			= 1 << 0
//,	INTEGER			= 1 << 1 | NUMBER
//,	FLOAT			= 1 << 2 | NUMBER
//,	BOOL			= 1 << 3
//,	CHAR			= 1 << 4
//,	APPLICATIVE		= 1 << 5
//,	FUNCTOR			= 1 << 6
//,	MONAD			= 1 << 7
//};

USTRUCT(BlueprintType)
struct FTypeData : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<class UStaticMesh> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Colour;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	ETypeTraits Traits;
};


/*
A Struct to hold information about a type
	Name, Image?, Child Types, Satisfies classes, COLOUR
A FlagEnum to hold information about acceptable types
An Enum to reference a specific Type
A way to relate the Enum to the FlagEnum

How I would like to do it

    Type   Name   
TYPE(Num, Number, Types


Realistic option:
Make a BitFlag for all types
Make the DataTable UE4 asset

*/


UCLASS()
class HONOURSPROJ_API UTypeHandler : public UObject {
	GENERATED_BODY()
public:
	UTypeHandler();

};
