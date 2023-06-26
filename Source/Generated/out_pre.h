// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MacroUtils.h"

#include "Preprocess/Include.h"

#ifndef PP__PREPROCESSING

#include "CoreMinimal.h"
#include "Types_gen.generated.h"

#else

include "CoreMinimal.h"
include "Types_gen.generated.h"

#endif



#define _ENUM_LOOP(ARGS) , IGNORE_FIRST ARGS PP__NEWLINE
#define _NAMESPACE_LOOP(NS, ITEM) , UNBRACKET ITEM = (uint8)NS::UNBRACKET ITEM PP__NEWLINE

#define _UENUM_BASE_LOOP(...) MAP_BLIST(_NAMESPACE_LOOP, __VA_ARGS__)

#define _UENUM_BASE(UENUM_SPECIFIERS, BASE, NAME, ...)				PP__NEWLINE \
_UENUM UENUM_SPECIFIERS												PP__NEWLINE \
enum class NAME : uint8 {											PP__NEWLINE \
	_UENUM_BASE_LOOP( BZIP(BASE, BRACKET_LIST2(__VA_ARGS__)))	PP__NEWLINE \
};																	PP__NEWLINE													

#define _CHILD_UENUMS(...) LOOP3(_UENUM_BASE, __VA_ARGS__)

// COMPOSITE_UENUM((Blueprint Specifiers), NAME, (Name, Members)...)
#define PP_COMPOSITE_UENUM(UENUM_SPECIFIERS, NAME, ...)	PP__NEWLINE \
_UENUM UENUM_SPECIFIERS									PP__NEWLINE \
enum class NAME : uint8 {								PP__NEWLINE \
	MAP_LIST(_ENUM_LOOP, __VA_ARGS__)					PP__NEWLINE \
};														PP__NEWLINE \
_CHILD_UENUMS(MZIP2((UENUM_SPECIFIERS, NAME), __VA_ARGS__)) 



#define PP_USTRUCT_LOOP(UPROP, MEMBER)	\
_UPROPERTY UPROP			PP__NEWLINE \
UNBRACKET MEMBER;			PP__NEWLINE 

// PP_USTRUCT((USTRUCT_SPECIFIER...), NAME, (UPROPERTY_SPECIFIER...), MEMBERS...)
#define PP_USTRUCT(USTRUCT_SPECIFIERS, NAME, UPROPERTY_SPECIFIERS, ...)	\
_USTRUCT USTRUCT_SPECIFIERS									PP__NEWLINE \
struct NAME {	PP__NEWLINE \
	_GENERATED_BODY()	PP__NEWLINE \
public:							PP__NEWLINE \
	LOOP(PP_USTRUCT_LOOP, BZIP2(UPROPERTY_SPECIFIERS, __VA_ARGS__)) \
};


// Define the Type UENUMS
PP_COMPOSITE_UENUM((BlueprintType), EType
	, (ETypeBase, INT, FLOAT, BOOL, CHAR)
	, (ETypeClass, 
ORDINAL, FUNCTOR
	)
	, (ETypeData,
NUMBER, MAYBE
	)
)

// Define the Type USTRUCT
PP_USTRUCT(
	(BlueprintType), FTypeInfo, 
	(EditAnywhere, BlueprintReadWrite), 
	(EType OuterType), 
	(TArray<EType> Templates)
)

//PP__PRE_DIRECTIVE(Print, Dict, Implementations)
//PP__PRE_DIRECTIVE(Print, Dict, Implementations, Key=Functor)
//PP__PRE_DIRECTIVE(Print, Dict, Implementations, Key=Ordinal)
