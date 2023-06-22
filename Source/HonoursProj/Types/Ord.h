#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"


// Functor Instance Macro
#define ORDINAL(TEMPLATES, INST, ORD)		\
TEMPLATE(UNBRACKET TEMPLATES)								\
TYPECLASS_DEFN(Ordinal, (), INST) {					\
	TYPECLASS_FUNC((), ord, ORD)							\
};

enum class ORD : int {
	LT = -1,
	EQ = 0,
	GT = 1
};

// Functor Class Template
template <typename A>
class Ordinal {
protected:
	template <class A>
	inline static Function<ORD, A, A> _ord;
	template <class A>
	inline static Function<bool, A, A> _lt;
	template <class A>
	inline static Function<bool, A, A> _lte;
	template <class A>
	inline static Function<bool, A, A> _gt;
	template <class A>
	inline static Function<bool, A, A> _gte;
	template <class A>
	inline static Function<bool, A, A> _eq;
	template <class A>
	inline static Function<bool, A, A> _neq;
	template <class A>
	inline static Function<A, A, A> _min;
	template <class A>
	inline static Function<A, A, A> _max;

public:
	template <class A>
	inline static auto ord = curry(Ordinal<A>::_ord<A>);
	template <class A>
	inline static auto lt = curry(Ordinal<A>::_lt<A>);
	template <class A>
	inline static auto lte = curry(Ordinal<A>::_lte<A>);
	template <class A>
	inline static auto gt = curry(Ordinal<A>::_gt<A>);
	template <class A>
	inline static auto gte = curry(Ordinal<A>::_gte<A>);
	template <class A>
	inline static auto eq = curry(Ordinal<A>::_eq<A>);
	template <class A>
	inline static auto neq = curry(Ordinal<A>::_neq<A>);
	template <class A>
	inline static auto min = curry(Ordinal<A>::_min<A>);
	template <class A>
	inline static auto max = curry(Ordinal<A>::_max<A>);
};

// Ordinal Base Instance
template <class A>
class BaseOrdinal {
protected:
	template <class A>
	inline static Function<ORD, A, A> _ord;

	template <class A>
	inline static auto _lt = [](A a, A b) -> bool {
		return Ordinal<A>::ord<A>(a)(b) == ORD::LT;
	};
	template <class A>
	inline static auto _lte = [](A a, A b) -> bool {
		return Ordinal<A>::ord(a)(b) != ORD::GT;
	};
	template <class A>
	inline static auto _gt = [](A a, A b) -> bool {
		return Ordinal<A>::ord(a)(b) == ORD::GT;
	};
	template <class A>
	inline static auto _gte = [](A a, A b) -> bool {
		return Ordinal<A>::ord(a)(b) != ORD::LT;
	};
	template <class A>
	inline static auto _eq = [](A a, A b) -> bool {
		return Ordinal<A>::ord(a)(b) == ORD::EQ;
	};
	template <class A>
	inline static auto _neq = [](A a, A b) -> bool {
		return Ordinal<A>::ord(a)(b) != ORD::EQ;
	};
	template <class A>
	inline static auto _min = [](A a, A b) -> A {
		return Ordinal<A>::ord(a)(b) == ORD::LT ? a : b;
	};
	template <class A>
	inline static auto _max = [](A a, A b) -> A {
		return Ordinal<A>::ord(a)(b) == ORD::GT ? a : b;
	};

public:
	template <class A>
	inline static auto ord = curry(_ord<A>);
	template <class A>
	inline static auto lt = curry(_lt<A>);
	template <class A>
	inline static auto lte = curry(_lte<A>);
	template <class A>
	inline static auto gt = curry(_gt<A>);
	template <class A>
	inline static auto gte = curry(_gte<A>);
	template <class A>
	inline static auto eq = curry(_eq<A>);
	template <class A>
	inline static auto neq = curry(_neq<A>);
	template <class A>
	inline static auto min = curry(_min<A>);
	template <class A>
	inline static auto max = curry(_max<A>);
};
