#pragma once

//// Functor Instance Macro
#define APPLICATIVE(INST)		 \
PP__DIRECTIVE(Typeclass, Applicative, INST)	

#define IAPPLICATIVE() 																PP__NEWLINE \
class Applicative : public virtual IApplicative, public virtual Functor {			PP__NEWLINE \
private:																			PP__NEWLINE \
	virtual VStar _pure(const VStar& value) const override;							PP__NEWLINE \
	virtual VStar _apply(const VStar& boxedFunc, const VStar& app) const override;	PP__NEWLINE \
public:																				PP__NEWLINE \
	Applicative() = default;														PP__NEWLINE \
}; 																					PP__NEWLINE \
inline static const Applicative ApplicativeInst = {};

#include "Applicative_gen.h"