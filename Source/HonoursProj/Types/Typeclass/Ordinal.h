#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Eq.h"

//#include "Types/Bool_gen.h"

#ifndef PP__PREPROCESSING

#include "Types/Bool_gen.h"

#else

include "Types/Bool_gen.h"

#endif

// Functor Instance Macro
#define ORDINAL(TEMPLATES, INST, ORD)				\
PP__DIRECTIVE(Typeclass, Ordinal, INST)				\
TEMPLATE(UNBRACKET TEMPLATES)						\
STATIC_TYPECLASS_DEFN(Ordinal, TEMPLATES, INST) {	\
	TYPECLASS_FUNC((), ord, ORD)					\
};

enum class ORD : int {
	LT = -1,
	EQ = 0,
	GT = 1
};




// Ordinal Interface
class IOrdinal : IEq {
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



// // Functor Class Template
// template <typename A>
// class Ordinal {
// protected:
// 	template <class _ = A>
// 	inline static Function<ORD, A, A> _ord;
// 	template <class _ = A>
// 	inline static Function<bool, A, A> _lt;
// 	template <class _ = A>
// 	inline static Function<bool, A, A> _lte;
// 	template <class _ = A>
// 	inline static Function<bool, A, A> _gt;
// 	template <class _ = A>
// 	inline static Function<bool, A, A> _gte;
// 	template <class _ = A>
// 	inline static Function<bool, A, A> _eq;
// 	template <class _ = A>
// 	inline static Function<bool, A, A> _neq;
// 	template <class _ = A>
// 	inline static Function<A, A, A> _min;
// 	template <class _ = A>
// 	inline static Function<A, A, A> _max;

// public:
// 	template <class _ = A>
// 	inline static auto ord = curry(Ordinal<A>::_ord<_>);
// 	template <class _ = A>
// 	inline static auto lt = curry(Ordinal<A>::_lt<_>);
// 	template <class _ = A>
// 	inline static auto lte = curry(Ordinal<A>::_lte<_>);
// 	template <class _ = A>
// 	inline static auto gt = curry(Ordinal<A>::_gt<_>);
// 	template <class _ = A>
// 	inline static auto gte = curry(Ordinal<A>::_gte<_>);
// 	template <class _ = A>
// 	inline static auto eq = curry(Ordinal<A>::_eq<_>);
// 	template <class _ = A>
// 	inline static auto neq = curry(Ordinal<A>::_neq<_>);
// 	template <class _ = A>
// 	inline static auto min = curry(Ordinal<A>::_min<_>);
// 	template <class _ = A>
// 	inline static auto max = curry(Ordinal<A>::_max<_>);
// };

// // Ordinal Base Instance
// template <class A>
// class BaseOrdinal {
// protected:
// 	template <class _ = A>
// 	inline static Function<ORD, A, A> _ord;

// 	template <class _ = A>
// 	inline static auto _lt = [](A a, A b) -> bool {
// 		return Ordinal<A>::template ord<_>(a)(b) == ORD::LT;
// 	};
// 	template <class _ = A>
// 	inline static auto _lte = [](A a, A b) -> bool {
// 		return Ordinal<A>::template ord<_>(a)(b) != ORD::GT;
// 	};
// 	template <class _ = A>
// 	inline static auto _gt = [](A a, A b) -> bool {
// 		return Ordinal<A>::template ord<_>(a)(b) == ORD::GT;
// 	};
// 	template <class _ = A>
// 	inline static auto _gte = [](A a, A b) -> bool {
// 		return Ordinal<A>::template ord<_>(a)(b) != ORD::LT;
// 	};
// 	template <class _ = A>
// 	inline static auto _eq = [](A a, A b) -> bool {
// 		return Ordinal<A>::template ord<_>(a)(b) == ORD::EQ;
// 	};
// 	template <class _ = A>
// 	inline static auto _neq = [](A a, A b) -> bool {
// 		return Ordinal<A>::template ord<_>(a)(b) != ORD::EQ;
// 	};
// 	template <class _ = A>
// 	inline static auto _min = [](A a, A b) -> A {
// 		return Ordinal<A>::template ord<_>(a)(b) == ORD::LT ? a : b;
// 	};
// 	template <class _ = A>
// 	inline static auto _max = [](A a, A b) -> A {
// 		return Ordinal<A>::template ord<_>(a)(b) == ORD::GT ? a : b;
// 	};

// public:
// 	template <class _ = A>
// 	inline static auto ord = curry(_ord<_>);
// 	template <class _ = A>
// 	inline static auto lt = curry(_lt<_>);
// 	template <class _ = A>
// 	inline static auto lte = curry(_lte<_>);
// 	template <class _ = A>
// 	inline static auto gt = curry(_gt<_>);
// 	template <class _ = A>
// 	inline static auto gte = curry(_gte<_>);
// 	template <class _ = A>
// 	inline static auto eq = curry(_eq<_>);
// 	template <class _ = A>
// 	inline static auto neq = curry(_neq<_>);
// 	template <class _ = A>
// 	inline static auto min = curry(_min<_>);
// 	template <class _ = A>
// 	inline static auto max = curry(_max<_>);
// };
