#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

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

// Functor Interface
class IEnum {
	// toEnum :: Int -> a
	TypeclassVirtual(VStar, toEnum, integer) = 0;
	// fromEnum :: a -> Int
	TypeclassVirtual(Int, fromEnum, value) = 0;

	// succ :: a -> a
	TypeclassVirtual(VStar, succ, value) {
		return toEnum()(fromEnum()(value).get() + 1);
	}
	// pred :: a -> a
	TypeclassVirtual(VStar, pred, value) {
		return toEnum()(fromEnum()(value).get() - 1);
	}
	// enumFrom :: a -> [a]
	// TypeclassVirtual(ListV, enumFrom, start) { return n : enumFrom (succ n)	}
	// enumFromThen :: a -> a -> [a]
	// TypeclassVirtual(ListV, enumFromThen, start) { ... }
	// enumFromTo :: a -> a -> [a]
	// TypeclassVirtual(ListV, enumFromTo, start) { ...	}
	// enumFromThenTo :: a -> a -> a -> [a]
	// TypeclassVirtual(ListV, enumFromThenTo, start) { ...	}
};



