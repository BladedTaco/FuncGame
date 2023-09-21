#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"



#ifndef PP__PREPROCESSING

#include "Types/Typeclass/Semigroup_gen.h"

#else

include "Types/Typeclass/Semigroup_gen.h"

#endif

;
// Functor Interface
class IMonoid : public virtual ISemigroup {
	// mempty :: a
	TypeclassVirtual(VStar, mempty) = 0;
	TypeclassVirtual(VStar, memptyV, monoid) { return monoid.getTypeclass()->Monoid->mempty(); }

	// mconcat :: [a] -> a
	// TypeclassVirtual(VStar, mconcat, list) {
	// 	return sconcat()(mempty() : list)
	// }
};



