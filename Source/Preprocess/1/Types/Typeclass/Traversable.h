#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"
#include "Types/FDecl.h"


#ifndef PP__PREPROCESSING

#include "Types/Typeclass/Foldable_gen.h"
#include "Types/Typeclass/Functor_gen.h"

#else

include "Types/Typeclass/Foldable_gen.h"
include "Types/Typeclass/Functor_gen.h"

#endif

;

// Functor Interface
class ITraversable : public virtual IFoldable, public virtual IFunctor {
	// traverse :: Applicative f => (a -> f b) -> t a -> f (t b) = 0;
	TypeclassVirtual(VStar, traverse, applic, f, foldable) = 0;
		// {
		// 	VStar mapped = fmap()(f)(foldable);
		// 	return sequenceA()(mapped);
		// };
	// sequenceA :: Applicative f => t (f a) -> f (t a)
	TypeclassVirtual(VStar, sequenceA, applic, foldable) {
		return traverse()(PreludeV::id)(foldable);
	};
};
