// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MacroUtils.h"


#ifndef __PREPROCESSING

#define __NEWLINE

//#include "CoreMinimal.h"


//#include "Types.generated.h"

#else

include "CoreMinimal.h"


include "Types_gen.generated.h"

#endif

#define _UENUM(...) UENUM(__VA_ARGS__)


#define _ENUM_LOOP(ARGS) , IGNORE_FIRST ARGS __NEWLINE
#define _NAMESPACE_LOOP(NS, ITEM) , UNBRACKET ITEM = (uint8)NS::UNBRACKET ITEM __NEWLINE

#define _UENUM_BASE_LOOP(...) MAP_BLIST(_NAMESPACE_LOOP, __VA_ARGS__)

#define _UENUM_BASE(UENUM_SPECIFIERS, BASE, NAME, ...)				__NEWLINE \
_UENUM UENUM_SPECIFIERS												__NEWLINE \
enum class NAME : uint8 {											__NEWLINE \
	_UENUM_BASE_LOOP( BZIP(BASE, BRACKET_LIST2(__VA_ARGS__)))	__NEWLINE \
};																	__NEWLINE													

#define _CHILD_UENUMS(...) LOOP3(_UENUM_BASE, __VA_ARGS__)

// COMPOSITE_UENUM((Blueprint Specifiers), NAME, (Name, Members)...)
#define COMPOSITE_UENUM(UENUM_SPECIFIERS, NAME, ...)	__NEWLINE \
_UENUM UENUM_SPECIFIERS									__NEWLINE \
enum class NAME : uint8 {								__NEWLINE \
	MAP_LIST(_ENUM_LOOP, __VA_ARGS__)					__NEWLINE \
};														__NEWLINE \
_CHILD_UENUMS(MZIP2((UENUM_SPECIFIERS, NAME), __VA_ARGS__)) 


COMPOSITE_UENUM((BlueprintType), EType
	, (EBaseType, NUMBER_INT, NUMBER_FLOAT, BOOL, CHAR)
	, (ETemplateType, MAYBE, FUNCTOR, ORDINAL, ARROW)
)






//UENUM(BlueprintType) 
//enum class EType : uint8 { 
//	APPLY(IGNORE_FIRST, (EPrimitiveType, NUMBER_INT, NUMBER_FLOAT, BOOL, CHAR))
//	, APPLY(IGNORE_FIRST, (ETemplateType, MAYBE, FUNCTOR, ORDINAL, ARROW)) 
//};
//NUMBER_INT, NUMBER_FLOAT, BOOL, CHAR 
//UENUM(BlueprintType) 
//enum class EPrimitiveType : uint8 { 
//	LOOP(_NAMESPACE_LOOP, APPLY(IGNORE_FIRST, (LOOP_I(BZIP_BASE, EType, APPLY(IGNORE_FIRST, (LOOP_I(TAKE_BASE, BRACKET, NUMBER_INT, NUMBER_FLOAT, BOOL, CHAR)))))))
//}; 
//MAYBE, FUNCTOR, ORDINAL, ARROW 
//UENUM(BlueprintType) 
//enum class ETemplateType : uint8 { 
//	LOOP(_NAMESPACE_LOOP, APPLY(IGNORE_FIRST, (LOOP_I(BZIP_BASE, EType, APPLY(IGNORE_FIRST, (LOOP_I(TAKE_BASE, BRACKET, MAYBE, FUNCTOR, ORDINAL, ARROW)))))))
//};
//

//
//UENUM(BlueprintType)
//enum class EType : uint8 {
//	NUMBER_INT
//,	NUMBER_FLOAT
//,	BOOL
//,	CHAR
//,	MAYBE
//,	FUNCTOR
//,	ORDINAL
//,	ARROW
//};
//
//
//UENUM(BlueprintType)
//enum class EPrimitiveTypes : uint8 {
//	NUMBER_INT = EType::NUMBER_INT
//,	NUMBER_FLOAT = EType::NUMBER_FLOAT
//,	BOOL = EType::BOOL
//,	CHAR = EType::CHAR
//};
//
//UENUM(BlueprintType)
//enum class ETemplatedTypes : uint8 {
//	MAYBE = EType::MAYBE
//,	FUNCTOR = EType::FUNCTOR
//,	ORDINAL = EType::ORDINAL
//,	ARROW = EType::ARROW
//};

//
//USTRUCT(BlueprintType)
//struct FType {
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere)
//	EType Type;
//
//	UPROPERTY(EditAnywhere)
//	TArray<FType> Templates;
//};
//
