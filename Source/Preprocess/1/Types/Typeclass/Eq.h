#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

;
// Functor Interface
class IEq {
	TypeclassVirtualDecl(Bool,  eq, a, b) = 0;
	TypeclassVirtualDecl(Bool, neq, a, b);
};



