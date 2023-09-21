#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"


// Functor Interface
class INum {
	// (+) :: a -> a -> a
	TypeclassVirtualDecl(VStar, plus, a, b) = 0;
	// (-) :: a -> a -> a
	TypeclassVirtualDecl(VStar, minus, a, b) = 0;
	// (*) :: a -> a -> a
	TypeclassVirtualDecl(VStar, times, a, b) = 0;
	// abs :: a -> a
	TypeclassVirtualDecl(VStar, abs, value) = 0;
	// signum :: a -> a
	TypeclassVirtualDecl(VStar, sign, value) = 0;
	// fromInteger :: Int -> a
	TypeclassVirtualDecl(VStar, fromInt, integer) = 0;

	// negate :: a -> a
	TypeclassVirtualDecl(VStar, negate, value);
};