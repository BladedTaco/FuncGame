#pragma once

//// Functor Instance Macro 
#define ALTERNATIVE(INST)		 \
PP__DIRECTIVE(Typeclass, Alternative, INST)

#include "Alternative_gen.h"