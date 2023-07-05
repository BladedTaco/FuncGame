// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MacroUtils.h"

#include "Preprocess/Include.h"

#ifndef PP__PREPROCESSING

#include "CoreMinimal.h"
#include "Types_gen.generated.h"

#else

include "CoreMinimal.h"
include "Algo/Transform.h"

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
	, (ETypeBase, NONE, INT, FLOAT, BOOL, CHAR)
	, (ETypeClass, ANY, PP__PRE_DIRECTIVE(Print, List, TypeClasses, Case = Capitalize))
	, (ETypeData, PP__PRE_DIRECTIVE(Print, List, DataClasses, Case = Capitalize))
)


// PP_TYPECLASS_MEMBERSHIP(TYPECLS, INSTS...)
#define PP_TRUE_CASE(INST) case EType::INST: return true; PP__NEWLINE


// PP_TYPECLASS_MEMBERSHIP(TYPECLS, INSTS...)
#define PP_TYPECLASS_MEMBERSHIP(TYPECLS, ...)						\
case EType::TYPECLS:									PP__NEWLINE \
	switch (lhs) {										PP__NEWLINE \
		LOOP2(PP_TRUE_CASE, BRACKET_LIST(__VA_ARGS__))				\
	default: return false;								PP__NEWLINE \
	}													PP__NEWLINE \
	break;												PP__NEWLINE

//PP_TYPECLASS_TESTS((TYPECLS, INSTS)...)
#define PP_TYPECLASS_TESTS(...)					\
switch (rhs) { PP__NEWLINE						\
	LOOP3(PP_TYPECLASS_MEMBERSHIP, __VA_ARGS__)	\
}

#define OPERATOR_IMPL(CLS, OP, IMPL) inline bool operator ## OP (const CLS lhs, const CLS rhs) { UNBRACKET IMPL } PP__NEWLINE

#define ALL_ORDINALS(CLS) \
OPERATOR_IMPL(CLS, > , (return   rhs < lhs; )) \
OPERATOR_IMPL(CLS, <=, (return !(lhs > rhs);)) \
OPERATOR_IMPL(CLS, >=, (return !(lhs < rhs);))

// Define Category like less than
inline bool operator< (const EType lhs, const EType rhs) {
	// Everything is less than any except any
	if (rhs == EType::ANY) { return lhs != EType::ANY; }
	// Loop through each Typeclass
	PP_TYPECLASS_TESTS(PP__PRE_DIRECTIVE(Print, Dict, Implementations, Case = Capitalize));
	// RHS is DataClass or Base, it cannot be greater
	return false;
}
ALL_ORDINALS(EType);




//
//
//
//
//
//_USTRUCT(BlueprintType)
//struct FTypeInfo {
//	_GENERATED_BODY()
//public:
//	virtual EType GetType() { return EType::ANY; };
//	virtual TArray<FTypeInfo> GetTemplates() { return {}; };
//};
//
//
//
//_USTRUCT(BlueprintType)
//struct FTypeConst : FTypeInfo {
//	_GENERATED_BODY()
//
//private:
//	UPROPERTY(VisibleAnywhere)
//		EType Type;
//	UPROPERTY(VisibleAnywhere)
//		TArray<FTypeInfo> Templates;
//
//public:
//	virtual EType GetType() override {
//		return Type;
//	};
//	virtual TArray<FTypeInfo> GetTemplates() override {
//		return Templates;
//	};
//};
//
//
//_USTRUCT(BlueprintType)
//struct FTypePtr : FTypeInfo {
//_GENERATED_BODY()
//
//private:
//	UPROPERTY(VisibleAnywhere)
//		TWeakPtr<FTypeInfo> Type;
//
//public:
//	virtual EType GetType() override {
//		return ( EType )Type.Pin().Get()->Templates[Index];
//	};
//	virtual TArray<FTypeInfo> GetTemplates() override {
//		return {};
//	};
//};
//
//
//
//USTRUCT(BlueprintType)
//struct FTypeInfo {
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		EType Type;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		bool Dependant;
//	FTypeInfo* DependsOn = NULL;
//	TArray<FTypeInfo> Templates;
//public:
//	// Base Constructor is Template Variable Constructor
//	FTypeInfo() : FTypeInfo(ETypeClass::ANY) {};
//	// Copy Constructor
//	FTypeInfo(const FTypeInfo& copy)
//		: Type(copy.Type)
//		, Templates({})
//		, Dependant(copy.Dependant)
//		, DependsOn(copy.DependsOn) {
//		// Dependant Types do not have copied templates
//		if (!Dependant) {
//			// Recursive copy
//			for (FTypeInfo i : copy.Templates) {
//				Templates.Add({ i });
//			}
//		}
//	};
//
//	// Base Type Constructor
//	FTypeInfo(ETypeBase type)
//		: Type(( EType )type)
//		, Templates({})
//		, Dependant(false)
//		, DependsOn(NULL) {};
//	// Data Type Constructor
//	FTypeInfo(ETypeData type, TArray<FTypeInfo> templates)
//		: Type(( EType )type)
//		, Templates(templates)
//		, Dependant(false)
//		, DependsOn(NULL) {};
//	// Class Type Constructor / Template Variable Constructor
//	FTypeInfo(ETypeClass type)
//		: Type(( EType )type)
//		, Templates({})
//		, Dependant(true)
//		, DependsOn(NULL) {};
//
//	// Template Variable Accessor Constructor
//	FTypeInfo(FTypeInfo* depends)
//		: Type(depends->Type)
//		, Templates(depends->Templates)
//		, Dependant(true)
//		, DependsOn(depends) {};
//};

//
//
//_USTRUCT(BlueprintType)
//struct FTypeVar {
//	_GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		ETypeClass Type;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		TWeakPtr<FTypeInfo> Instance;
//};


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

