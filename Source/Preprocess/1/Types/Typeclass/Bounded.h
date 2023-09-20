#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define BOUNDED(INST)		 \
PP__DIRECTIVE(Typeclass, Bounded, INST)


#define IBOUNDED() 									PP__NEWLINE \
class Bounded : public virtual IBounded {			PP__NEWLINE \
private:											PP__NEWLINE \
	virtual VStar _minBound() const override;		PP__NEWLINE \
	virtual VStar _maxBound() const override;		PP__NEWLINE \
public:												PP__NEWLINE \
	Bounded() = default;							PP__NEWLINE \
}; 													PP__NEWLINE \
inline static const Bounded BoundedInst = {};

// Functor Interface
class IBounded {
	TypeclassVirtual(VStar, minBound) = 0;
	TypeclassVirtual(VStar, maxBound) = 0;
};



