#pragma once


//// Functor Instance Macro
#define MONAD(INST)		 \
PP__DIRECTIVE(Typeclass, Monad, INST)


#define IMONAD() 																	PP__NEWLINE \
class Monad : public virtual IMonad, public virtual Applicative {					PP__NEWLINE \
private:																			PP__NEWLINE \
	virtual VStar _bind(const VStar& m_a, const VStar& a_to_mb) const override;		PP__NEWLINE \
public:																				PP__NEWLINE \
	Monad() = default;																PP__NEWLINE \
}; 																					PP__NEWLINE \
inline static const Monad MonadInst = {};


#include "Monad_gen.h"