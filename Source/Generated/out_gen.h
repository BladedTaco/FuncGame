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
include "Algo/Transform.h"
include "Types_gen.generated.h"

#line 22 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"









































PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class EType : uint8 { PP__NEWLINE NONE, INT, FLOAT, BOOL, CHAR PP__NEWLINE , ANY, FUNCTOR, ORDINAL PP__NEWLINE , ARROW, NUMBER, MAYBE PP__NEWLINE PP__NEWLINE }; PP__NEWLINE PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class ETypeBase : uint8 { PP__NEWLINE NONE = (uint8)EType::NONE PP__NEWLINE , INT = (uint8)EType::INT PP__NEWLINE , FLOAT = (uint8)EType::FLOAT PP__NEWLINE , BOOL = (uint8)EType::BOOL PP__NEWLINE , CHAR = (uint8)EType::CHAR PP__NEWLINE PP__NEWLINE }; PP__NEWLINE PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class ETypeClass : uint8 { PP__NEWLINE ANY = (uint8)EType::ANY PP__NEWLINE , FUNCTOR = (uint8)EType::FUNCTOR PP__NEWLINE , ORDINAL = (uint8)EType::ORDINAL PP__NEWLINE PP__NEWLINE }; PP__NEWLINE PP__NEWLINE UENUM(BlueprintType) PP__NEWLINE enum class ETypeData : uint8 { PP__NEWLINE ARROW = (uint8)EType::ARROW PP__NEWLINE , NUMBER = (uint8)EType::NUMBER PP__NEWLINE , MAYBE = (uint8)EType::MAYBE PP__NEWLINE PP__NEWLINE }; PP__NEWLINE

































inline bool operator< (const EType lhs, const EType rhs) {
	
	if (rhs == EType::ANY) { return lhs != EType::ANY; }
	
	switch (rhs) { PP__NEWLINE case EType::FUNCTOR: PP__NEWLINE switch (lhs) { PP__NEWLINE case EType::ARROW: return true; PP__NEWLINE case EType::MAYBE: return true; PP__NEWLINE default: return false; PP__NEWLINE } PP__NEWLINE break; PP__NEWLINE case EType::ORDINAL: PP__NEWLINE switch (lhs) { PP__NEWLINE case EType::NUMBER: return true; PP__NEWLINE default: return false; PP__NEWLINE } PP__NEWLINE break; PP__NEWLINE } ;
	
	return false;
}
inline bool operator > (const EType lhs, const EType rhs) { return rhs < lhs; } PP__NEWLINE inline bool operator <= (const EType lhs, const EType rhs) { return !(lhs > rhs); } PP__NEWLINE inline bool operator >= (const EType lhs, const EType rhs) { return !(lhs < rhs); } PP__NEWLINE ;




















































































































































