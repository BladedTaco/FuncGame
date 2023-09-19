#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define ENUM(INST)		 \
PP__DIRECTIVE(Typeclass, Enum, INST)

// Functor Interface
class IEnum {
	TypeclassVirtual(VStar, toEnum, integer) = 0;
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



