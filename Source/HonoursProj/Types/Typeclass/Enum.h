#pragma once

//// Functor Instance Macro
#define ENUM(INST)		 \
PP__DIRECTIVE(Typeclass, Enum, INST)


#define IENUM() 													PP__NEWLINE \
class Enum : public virtual IEnum {									PP__NEWLINE \
private:															PP__NEWLINE \
	virtual VStar _toEnum(const VStar& integer) const override;		PP__NEWLINE \
	virtual Int _fromEnum(const VStar& value) const override;		PP__NEWLINE \
public:																PP__NEWLINE \
	Enum() = default;												PP__NEWLINE \
}; 																	PP__NEWLINE \
inline static const Enum EnumInst = {};

#include "Enum_gen.h"