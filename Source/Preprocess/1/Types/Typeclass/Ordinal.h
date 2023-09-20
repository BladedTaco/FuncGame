#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Eq_gen.h"

//#include "Types/Bool_gen.h"

#ifndef PP__PREPROCESSING

#include "Types/Bool_gen.h"

#else

include "Types/Bool_gen.h"

#endif

// Functor Instance Macro
#define ORDINAL(INST)				\
PP__DIRECTIVE(Typeclass, Ordinal, INST)

#define IORDINAL() 															PP__NEWLINE \
class Ordinal : public virtual IOrdinal {									PP__NEWLINE \
private:																	PP__NEWLINE \
	virtual Ord _ord( const VStar& a, const VStar& b) const override;		PP__NEWLINE \
public:																		PP__NEWLINE \
	Ordinal() = default;													PP__NEWLINE \
}; 																			PP__NEWLINE \
inline static const Ordinal OrdinalInst = {};

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
	TypeclassVirtual(ORD,	ord, a, b) = 0;
	TypeclassVirtual(Bool,	lt , a, b) { return _ord(a, b) == ORD::LT; };
	TypeclassVirtual(Bool,	lte, a, b) { return _ord(a, b) != ORD::GT; };
	TypeclassVirtual(Bool,	gt , a, b) { return _ord(a, b) == ORD::GT; };
	TypeclassVirtual(Bool,	gte, a, b) { return _ord(a, b) != ORD::LT; };
	TypeclassVirtual(VStar, min, a, b) { return _ord(a, b) == ORD::LT ? a : b; };
	TypeclassVirtual(VStar, max, a, b) { return _ord(a, b) == ORD::GT ? a : b; };
	TypeclassVirtualOverride(Bool,	eq , a, b) { return _ord(a, b) == ORD::EQ; };
	TypeclassVirtualOverride(Bool,	neq, a, b) { return _ord(a, b) != ORD::EQ; };
};