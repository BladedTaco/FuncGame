#pragma once

// Implementing an Arrow TypeClass may need to be done in the future, but for now we can bystep it.
// This is done through handling partially applied functions seperately


//#include "MacroUtils.h"
//
//#include "Functional/Prelude.h"
//#include "Functional/Typeclass.h"
//
//// Functor Instance Macro
//#define ARROW(TEMPLATES, INST, ARR, FIRST)	 \
//PP__DIRECTIVE(Typeclass, Arrow, INST)		 \
//TEMPLATE(UNBRACKET TEMPLATES)				 \
//TYPECLASS_DEFN(Arrow, TEMPLATES, INST) {	 \
//	TYPECLASS_FUNC((B), arrow, ARR)			 \
//	TYPECLASS_FUNC((B), first, FIRST)		 \
//};
//
