#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Semigroup.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define Monoid(INST)		 \
PP__DIRECTIVE(Typeclass, Monoid, INST)

// Functor Interface
class IMonoid : ISemigroup {
	// mempty :: a
	TypeclassVirtual(VStar, mempty) = 0;

	// mconcat :: [a] -> a
	// TypeclassVirtual(VStar, mconcat, list) {
	// 	return sconcat()(mempty() : list)
	// }
};



