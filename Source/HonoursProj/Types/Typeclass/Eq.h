#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define EQ(INST)		 \
PP__DIRECTIVE(Typeclass, Eq, INST)

// Functor Interface
class IEq {
	TypeclassVirtual(Bool,  eq, a, b) = 0;
	TypeclassVirtual(Bool, neq, a, b) { return Bool(!eq()(a)(b).get()); }
};



