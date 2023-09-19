#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define NUM(INST)		 \
PP__DIRECTIVE(Typeclass, Num, INST)

// Functor Interface
class INum {
	// (+) :: a -> a -> a
	TypeclassVirtual(VStar, plus, a, b) = 0;
	// (-) :: a -> a -> a
	TypeclassVirtual(VStar, minus, a, b) = 0;
	// (*) :: a -> a -> a
	TypeclassVirtual(VStar, times, a, b) = 0;
	// abs :: a -> a
	TypeclassVirtual(VStar, abs, value) = 0;
	// signum :: a -> a
	TypeclassVirtual(VStar, sign, value) = 0;
	// fromInteger :: Int -> a
	TypeclassVirtual(VStar, fromInt, integer) = 0;

	// negate :: a -> a
	TypeclassVirtual(VStar, negate, value) {
		VStar zero = fromInt()(IntV(0));
		return minus()(zero)(value);
	}
};