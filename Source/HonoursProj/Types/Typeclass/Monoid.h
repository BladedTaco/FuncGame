#pragma once

//// Functor Instance Macro
#define MONOID(INST)		 \
PP__DIRECTIVE(Typeclass, Monoid, INST)


#define IMONOID() 													PP__NEWLINE \
class Monoid : public virtual IMonoid, public virtual Semigroup {	PP__NEWLINE \
private:															PP__NEWLINE \
	virtual VStar _mempty() const override;							PP__NEWLINE \
public:																PP__NEWLINE \
	Monoid() = default;												PP__NEWLINE \
}; 																	PP__NEWLINE \
inline static const Monoid MonoidInst = {};


#include "Monoid_gen.h"