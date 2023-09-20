#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Semigroup_gen.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define MONOID(INST)		 \
PP__DIRECTIVE(Typeclass, Monoid, INST)


#define IMONOID() 								PP__NEWLINE \
class Monoid : public virtual IMonoid {			PP__NEWLINE \
private:										PP__NEWLINE \
	virtual VStar _mempty() const override;		PP__NEWLINE \
public:											PP__NEWLINE \
	Monoid() = default;							PP__NEWLINE \
}; 												PP__NEWLINE \
inline static const Monoid MonoidInst = {};


// Functor Interface
class IMonoid : public virtual ISemigroup {
	// mempty :: a
	TypeclassVirtual(VStar, mempty) = 0;
	TypeclassVirtualT1(VStar, memptyV, monoid) { return monoid->Monoid->mempty(); }

	// mconcat :: [a] -> a
	// TypeclassVirtual(VStar, mconcat, list) {
	// 	return sconcat()(mempty() : list)
	// }
};



