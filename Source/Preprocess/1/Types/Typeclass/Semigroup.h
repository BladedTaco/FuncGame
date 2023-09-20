#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

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

// Functor Interface
class ISemigroup {
	// (<>) :: a -> a -> a
	TypeclassVirtual(VStar, mappend, left, right) = 0;
	// sconcat :: NonEmpty a -> a
	// Nonempty = a :| []
	// TypeclassVirtual(VStar, sconcat, list) {};
	// stimes :: Int -> a -> a
	TypeclassVirtual(VStar, stimes, times, group) {
		VStar value = group;
		for (int i = times.get<Int>().get(); i --> 2;) {
			value = mappend()(value)(group);
		}
		return value;
	};
};



