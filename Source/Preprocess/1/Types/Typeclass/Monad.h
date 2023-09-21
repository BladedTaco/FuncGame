#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"


#include "Types/Unpack.h"


#ifndef PP__PREPROCESSING

#include "Types/Typeclass/Applicative_gen.h"

#else

include "Types/Typeclass/Applicative_gen.h"

#endif

;
// Functor Interface
class IMonad : public virtual IApplicative {
	// (>>=) :: forall a b. m a -> (a -> m b) -> m b
	TypeclassVirtual(VStar, bind, m_a, a_to_mb) = 0;

	// (>>) :: forall a b. m a -> m b -> m b 
	TypeclassVirtual(VStar, then, m_a, m_b) {
		return bind()(m_a)(PreludeV::constant(m_b));
	}
	// return :: a -> m a
	TypeclassVirtual(VStar, mpure, value) {
		return pure()(value);
	}
};



