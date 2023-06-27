#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"


#pragma once

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"


#pragma once
#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\HonoursProj\\LoopMacros.h"


#pragma once














































































































































































































#line 5 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"





































































































































































#line 6 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Preprocess/Include.h"
#pragma once













#line 16 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Preprocess/Include.h"






#line 8 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"








include "CoreMinimal.h"
include "Types_gen.generated.h"

#line 20 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"









































PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class EType : uint8 { PP__NEWLINE INT, FLOAT, BOOL, CHAR, TEMPLATE PP__NEWLINE , ARROW, ORDINAL, FUNCTOR PP__NEWLINE , NUMBER, MAYBE PP__NEWLINE PP__NEWLINE }; PP__NEWLINE PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class ETypeBase : uint8 { PP__NEWLINE INT = (uint8)EType::INT PP__NEWLINE , FLOAT = (uint8)EType::FLOAT PP__NEWLINE , BOOL = (uint8)EType::BOOL PP__NEWLINE , CHAR = (uint8)EType::CHAR PP__NEWLINE , TEMPLATE = (uint8)EType::TEMPLATE PP__NEWLINE PP__NEWLINE }; PP__NEWLINE PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class ETypeClass : uint8 { PP__NEWLINE ARROW = (uint8)EType::ARROW PP__NEWLINE , ORDINAL = (uint8)EType::ORDINAL PP__NEWLINE , FUNCTOR = (uint8)EType::FUNCTOR PP__NEWLINE PP__NEWLINE }; PP__NEWLINE PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class ETypeData : uint8 { PP__NEWLINE NUMBER = (uint8)EType::NUMBER PP__NEWLINE , MAYBE = (uint8)EType::MAYBE PP__NEWLINE PP__NEWLINE }; PP__NEWLINE





USTRUCT(BlueprintType)
struct FTypeInfo {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EType Type;
	FTypeInfo* DependsOn = NULL;
	TArray<FTypeInfo> Templates;
public:
	FTypeInfo()
		: Type(EType::TEMPLATE)
		, Templates({})
		, DependsOn(NULL) {};
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


USTRUCT(BlueprintType)
struct FParameter {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTypeInfo Type;
public:
	FParameter()
		: Type()
		, Name("Unnamed") {};
	FParameter(FString name, FTypeInfo type)
		: Type(Type)
		, Name(name) {};
};

USTRUCT(BlueprintType)
struct FFunctionInfo {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Inputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParameter> Outputs;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTypeInfo> Templates;
};


























