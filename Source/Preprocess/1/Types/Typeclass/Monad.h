#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Applicative_gen.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define MONAD(INST)		 \
PP__DIRECTIVE(Typeclass, Monad, INST)


#define IMONAD() 																	PP__NEWLINE \
class Monad : public virtual IMonad {												PP__NEWLINE \
private:																			PP__NEWLINE \
	virtual VStar _bind(const VStar& m_a, const VStar& a_to_mb) const override;		PP__NEWLINE \
public:																				PP__NEWLINE \
	Monad() = default;																PP__NEWLINE \
}; 																					PP__NEWLINE \
inline static const Monad MonadInst = {};


// Functor Interface
class IMonad : public virtual IApplicative {
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



