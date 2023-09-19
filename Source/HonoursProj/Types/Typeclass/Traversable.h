#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Foldable.h"
#include "Types/Typeclass/Functor.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define TRAVERSABLE(INST)		 \
PP__DIRECTIVE(Typeclass, Traversable, INST)

// Functor Interface
class ITraversable : IFoldable, IFunctor {
	// traverse :: Applicative f => (a -> f b) -> t a -> f (t b) = 0;
	// sequenceA :: Applicative f => t (f a) -> f (t a)
	// mapM :: Monad m => (a -> m b) -> t a -> m (t b)
	// sequence :: Monad m => t (m a) -> m (t a)
};



