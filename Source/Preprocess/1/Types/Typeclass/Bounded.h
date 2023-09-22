#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"
;
// Functor Interface
class IBounded {
	TypeclassVirtual(VStar, minBound) = 0;
	TypeclassVirtual(VStar, maxBound) = 0;
};



