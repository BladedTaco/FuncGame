// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MacroUtils.h"

#include "Preprocess/Include.h"

#ifndef PP__PREPROCESSING

#include "CoreMinimal.h"
#include "Algo/Transform.h"
#include "Types_gen.generated.h"

#else

include "CoreMinimal.h"
include "Algo/Transform.h"
include "Types_gen.generated.h"

#endif



#define _ENUM_LOOP(ARGS) , IGNORE_FIRST ARGS PP__NEWLINE
#define _NAMESPACE_LOOP(NS, ITEM) , UNBRACKET ITEM = (uint8)NS::UNBRACKET ITEM PP__NEWLINE

#define _UENUM_BASE_LOOP(...) MAP_BLIST(_NAMESPACE_LOOP, __VA_ARGS__)

#define _UENUM_BASE(UENUM_SPECIFIERS, BASE, NAME, ...)			PP__NEWLINE \
_UENUM UENUM_SPECIFIERS											PP__NEWLINE \
enum class NAME : uint8 {										PP__NEWLINE \
	_UENUM_BASE_LOOP( BZIP(BASE, BRACKET_LIST2(__VA_ARGS__)))	PP__NEWLINE \
};																PP__NEWLINE													

#define _CHILD_UENUMS(...) LOOP3(_UENUM_BASE, __VA_ARGS__)

// COMPOSITE_UENUM((Blueprint Specifiers), NAME, (Name, Members)...)
#define PP_COMPOSITE_UENUM(UENUM_SPECIFIERS, NAME, ...)	PP__NEWLINE \
_UENUM UENUM_SPECIFIERS									PP__NEWLINE \
enum class NAME : uint8 {								PP__NEWLINE \
	MAP_LIST(_ENUM_LOOP, __VA_ARGS__)					PP__NEWLINE \
};														PP__NEWLINE \
_CHILD_UENUMS(MZIP2((UENUM_SPECIFIERS, NAME), __VA_ARGS__)) 



#define PP_USTRUCT_LOOP(UPROP, MEMBER)	\
NULLARY((_UPROPERTY UPROP PP__NEWLINE), (), UNBRACKET UPROP)	\
UNBRACKET MEMBER;									PP__NEWLINE 

// PP_USTRUCT((USTRUCT_SPECIFIER...), NAME, (UPROPERTY_SPECIFIER, MEMBER)...)
#define PP_USTRUCT(USTRUCT_SPECIFIERS, NAME, ...)	\
_USTRUCT USTRUCT_SPECIFIERS				PP__NEWLINE \
struct NAME {							PP__NEWLINE \
	_GENERATED_BODY()					PP__NEWLINE \
public:									PP__NEWLINE \
	LOOP(PP_USTRUCT_LOOP, __VA_ARGS__)				\
};


// Define the Type UENUMS
PP_COMPOSITE_UENUM((BlueprintType), EType
	, (ETypeBase, INT, FLOAT, BOOL, CHAR, TEMPLATE)
	, (ETypeClass, ARROW, PP__PRE_DIRECTIVE(Print, List, TypeClasses, Case=Capitalize))
	, (ETypeData, PP__PRE_DIRECTIVE(Print, List, DataClasses, Case=Capitalize))
)

USTRUCT(BlueprintType)
struct FTypeInfo {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EType Type;
	FTypeInfo* DependsOn = NULL;
	TArray<FTypeInfo> Templates;
public:
	// Base Constructor
	FTypeInfo()
		: Type(EType::TEMPLATE)
		, Templates({})
		, DependsOn(NULL) {};
	// Copy Constructor
	FTypeInfo(const FTypeInfo& copy)
		: Type(copy.Type)
		, Templates({})
		, DependsOn(copy.DependsOn) {
		// Recursive copy
		for (FTypeInfo i : copy.Templates) {
			Templates.Add({ i });
		}
	};
	// Ohter Constructors
	FTypeInfo(ETypeBase type)
		: Type(( EType )type)
		, Templates({})
		, DependsOn(NULL) {};
	FTypeInfo(FTypeInfo* depends)
		: Type(depends->Type)
		, Templates(depends->Templates)
		, DependsOn(depends) {};
	FTypeInfo(EType type, TArray<FTypeInfo> templates)
		: Type(type)
		, Templates(templates)
		, DependsOn(NULL) {};
	FTypeInfo(FTypeInfo* depends, TArray<FTypeInfo> templates)
		: Type(depends->Type)
		, Templates(templates)
		, DependsOn(depends) {};
};


_USTRUCT(BlueprintType)
struct FParameter {
	_GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTypeInfo Type;
public:
	// Base Constructor
	FParameter()
		: Type()
		, Name("Unnamed") {};
	// Copy Constructor
	FParameter(FParameter& copy)
		: Type({ copy.Type })
		, Name(copy.Name) {};
	// Other Constructors
	FParameter(FString name, FTypeInfo type)
		: Type(Type)
		, Name(name) {};
};

_USTRUCT(BlueprintType)
struct FFunctionInfo {
	_GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Inputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Outputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTypeInfo> Templates;
public:
	// Base Constructor
	FFunctionInfo()
		: Inputs({})
		, Outputs({})
		, Templates({}) {};
	// Copy Constructor
	FFunctionInfo(FFunctionInfo& copy)
		: Inputs({})
		, Outputs({})
		, Templates({}) {
		for (FParameter i : copy.Inputs) {
			Inputs.Add({ i });
		}
		for (FParameter i : copy.Outputs) {
			Outputs.Add({ i });
		}
		for (FTypeInfo i : copy.Templates) {
			Templates.Add({ i });
		}
	};
};



//// Define the Type USTRUCT
//PP_USTRUCT(
//	(BlueprintType), FTypeInfo
//,  	((EditAnywhere, BlueprintReadWrite), (EType Type))
//,  	((), (FTypeInfo* DependsOn = NULL))
//,	((), (TArray<FTypeInfo> Templates))
//)
//
//
//
//PP__NEWLINE
//
//// Define the Function USTRUCT
//PP_USTRUCT(
//	(BlueprintType), FFunctionInfo
//,	((EditAnywhere, BlueprintReadWrite), (TArray<FTypeInfo> Inputs))
//,	((EditAnywhere, BlueprintReadWrite), (TArray<FTypeInfo> Outputs))
//)


//PP__PRE_DIRECTIVE(Print, Dict, Implementations)
//PP__PRE_DIRECTIVE(Print, Dict, Implementations, Key=Functor)
//PP__PRE_DIRECTIVE(Print, Dict, Implementations, Key=Ordinal)