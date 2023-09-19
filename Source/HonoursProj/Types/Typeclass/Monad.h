#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Applicative.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define MONAD(INST)		 \
PP__DIRECTIVE(Typeclass, Monad, INST)

// Functor Interface
class IMonad : IApplicative {
	// (>>=) :: forall a b. m a -> (a -> m b) -> m b
	TypeclassVirtual(VStar, bind, m_a, a_to_mb) = 0;

	// (>>) :: forall a b. m a -> m b -> m b 
	TypeclassVirtual(VStar, then, m_a, m_b) {
		return bind()(m_a)(Prelude::Constant<VStar, VStar>(m_b));
	}
	// return :: a -> m a
	TypeclassVirtual(VStar, return, value) {
		return pure()(value);
	}
};



