#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Applicative_gen.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define ALTERNATIVE(INST)		 \
PP__DIRECTIVE(Typeclass, Alternative, INST)



// Functor Interface
class IAlternative : IApplicative {
	// TypeclassVirtual(VStar, )
};

/*
https://hackage.haskell.org/package/base-4.16.3.0/docs/Control-Applicative.html#t:Alternative

    -- | The identity of '<|>'
    empty :: f a
    -- | An associative binary operation
    (<|>) :: f a -> f a -> f a

    -- | One or more.
    some :: f a -> f [a]
    some v = some_v
      where
        many_v = some_v <|> pure []
        some_v = liftA2 (:) v many_v

    -- | Zero or more.
    many :: f a -> f [a]
    many v = many_v
      where
        many_v = some_v <|> pure []
        some_v = liftA2 (:) v many_v
*/

