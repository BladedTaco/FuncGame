#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"


#ifndef PP__PREPROCESSING

#include "Types/Typeclass/Eq_gen.h"

#else

include "Types/Typeclass/Eq_gen.h"

#endif

// // Functor Instance Macro
// #define ORDINAL(TEMPLATES, INST, ORD)				\
// PP__DIRECTIVE(Typeclass, Ordinal, INST)				\
// TEMPLATE(UNBRACKET TEMPLATES)						\
// STATIC_TYPECLASS_DEFN(Ordinal, TEMPLATES, INST) {	\
// 	TYPECLASS_FUNC((), ord, ORD)					\
// };

enum class ORD : int {
	LT = -1,
	EQ = 0,
	GT = 1
};


// Ordinal Interface
class IOrdinal : public virtual IEq {
	TypeclassVirtualDecl(ORD,	ord, a, b) = 0;
	TypeclassVirtualDecl(Bool,	lt , a, b);// { return _ord(a, b) == ORD::LT; };
	TypeclassVirtualDecl(Bool,	lte, a, b);// { return _ord(a, b) != ORD::GT; };
	TypeclassVirtualDecl(Bool,	gt , a, b);// { return _ord(a, b) == ORD::GT; };
	TypeclassVirtualDecl(Bool,	gte, a, b);// { return _ord(a, b) != ORD::LT; };
	TypeclassVirtualDecl(VStar, min, a, b);// { return _ord(a, b) == ORD::LT ? a : b; };
	TypeclassVirtualDecl(VStar, max, a, b);// { return _ord(a, b) == ORD::GT ? a : b; };
	TypeclassVirtualOverride(Bool,	eq , a, b);// { return _ord(a, b) == ORD::EQ; };
	TypeclassVirtualOverride(Bool,	neq, a, b);// { return _ord(a, b) != ORD::EQ; };
};