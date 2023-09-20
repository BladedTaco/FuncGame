#pragma once

// UNUSED

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define READ(INST)		 \
PP__DIRECTIVE(Typeclass, Read, INST)

// Functor Interface
class IRead {
};



