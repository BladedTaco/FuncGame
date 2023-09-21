#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"




// Functor Interface
class IFunctor {
	// fmap :: (a -> b) -> f a -> f b
	TypeclassVirtual(VStar,	fmap, f, f_a) = 0;
	// (<$) :: a -> f b -> f a
	TypeclassVirtual(VStar, map_replace_by, a, f_b) { 
		Arr<VStar, VStar> f = { PreludeV::constant(a) };
		return _fmap(f, f_b);
	};
};



