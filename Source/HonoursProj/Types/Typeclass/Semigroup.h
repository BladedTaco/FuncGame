#pragma once



//// Functor Instance Macro
#define SEMIGROUP(INST)		 \
PP__DIRECTIVE(Typeclass, Semigroup, INST)

#define ISEMIGROUP() 																	PP__NEWLINE \
class Semigroup : public virtual ISemigroup {											PP__NEWLINE \
private:																				PP__NEWLINE \
	virtual VStar _mappend( const VStar& left, const VStar& right) const override;		PP__NEWLINE \
public:																					PP__NEWLINE \
	Semigroup() = default;																PP__NEWLINE \
}; 																						PP__NEWLINE \
inline static const Semigroup SemigroupInst = {};


#include "Semigroup_gen.h"