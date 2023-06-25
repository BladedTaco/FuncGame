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
#define COMPOSITE_UENUM(UENUM_SPECIFIERS, NAME, ...)	PP__NEWLINE \
_UENUM UENUM_SPECIFIERS									PP__NEWLINE \
enum class NAME : uint8 {								PP__NEWLINE \
	MAP_LIST(_ENUM_LOOP, __VA_ARGS__)					PP__NEWLINE \
};														PP__NEWLINE \
_CHILD_UENUMS(MZIP2((UENUM_SPECIFIERS, NAME), __VA_ARGS__)) 


COMPOSITE_UENUM((BlueprintType), EType
	, (EBaseType, NUMBER_INT, NUMBER_FLOAT, BOOL, CHAR)
	, (ETemplateType, 
		PP__PRE_DIRECTIVE(Print, TypeClasses)
	)
)


//, (ETemplateType, MAYBE, FUNCTOR, ORDINAL, ARROW)


