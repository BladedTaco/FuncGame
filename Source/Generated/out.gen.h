#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Types.h"


#pragma once

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"


#pragma once
#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\HonoursProj\\LoopMacros.h"


#pragma once














































































































































































































#line 5 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"





































































































































































#line 6 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Types.h"













include "CoreMinimal.h"


include "Types.gen.generated.h"

#line 25 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Types.h"


























__NEWLINE UENUM(BlueprintType) __NEWLINE enum class EType : uint8 { __NEWLINE NUMBER_INT, NUMBER_FLOAT, BOOL, CHAR __NEWLINE , MAYBE, FUNCTOR, ORDINAL, ARROW __NEWLINE __NEWLINE }; __NEWLINE __NEWLINE UENUM(BlueprintType) __NEWLINE enum class EPrimitiveType : uint8 { __NEWLINE NUMBER_INT = (uint8)EType::NUMBER_INT __NEWLINE , NUMBER_FLOAT = (uint8)EType::NUMBER_FLOAT __NEWLINE , BOOL = (uint8)EType::BOOL __NEWLINE , CHAR = (uint8)EType::CHAR __NEWLINE __NEWLINE }; __NEWLINE __NEWLINE UENUM(BlueprintType) __NEWLINE enum class ETemplateType : uint8 { __NEWLINE MAYBE = (uint8)EType::MAYBE __NEWLINE , FUNCTOR = (uint8)EType::FUNCTOR __NEWLINE , ORDINAL = (uint8)EType::ORDINAL __NEWLINE , ARROW = (uint8)EType::ARROW __NEWLINE __NEWLINE }; __NEWLINE




































































