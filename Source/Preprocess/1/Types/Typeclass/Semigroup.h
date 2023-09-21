#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"


// Functor Interface
class ISemigroup {
	// (<>) :: a -> a -> a
	TypeclassVirtual(VStar, mappend, left, right) = 0;
	// sconcat :: NonEmpty a -> a
	// Nonempty = a :| []
	// TypeclassVirtual(VStar, sconcat, list) {};
	// stimes :: Int -> a -> a
	TypeclassVirtualDecl(VStar, stimes, times, group);
};



