#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"


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
class IOrdinal {
public: 
	const auto ord() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_ord(a, b); });
}; 
private: 
	virtual ORD _ord(const VStar& a, const VStar& b) const = 0;
public: const auto lt() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_lt(a, b); });
}; private: virtual bool _lt(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::LT; };
public: const auto lte() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_lte(a, b); });
}; private: virtual bool _lte(const VStar& a, const VStar& b) const { return _ord(a, b) != ORD::GT; };
public: const auto gt() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_gt(a, b); });
}; private: virtual bool _gt(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::GT; };
public: const auto gte() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_gte(a, b); });
}; private: virtual bool _gte(const VStar& a, const VStar& b) const { return _ord(a, b) != ORD::LT; };
public: const auto eq() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_eq(a, b); });
}; private: virtual bool _eq(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::EQ; };
public: const auto neq() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_neq(a, b); });
}; private: virtual bool _neq(const VStar& a, const VStar& b) const { return _ord(a, b) != ORD::EQ; };
public: const auto min() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_min(a, b); });
}; private: virtual VStar _min(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::LT ? a : b; };
public: const auto max() const {
	return curry([this](const VStar& a, const VStar& b) { return this->_max(a, b); });
}; private: virtual VStar _max(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::GT ? a : b; };
};



//
//// Ordinal Interface
//class IOrdinal {
//	TypeclassVirtual(ORD,	ord, a, b) = 0;
//	TypeclassVirtual(bool,	lt , a, b) { return _ord(a, b) == ORD::LT; };
//	TypeclassVirtual(bool,	lte, a, b) { return _ord(a, b) != ORD::GT; };
//	TypeclassVirtual(bool,	gt , a, b) { return _ord(a, b) == ORD::GT; };
//	TypeclassVirtual(bool,	gte, a, b) { return _ord(a, b) != ORD::LT; };
//	TypeclassVirtual(bool,	eq , a, b) { return _ord(a, b) == ORD::EQ; };
//	TypeclassVirtual(bool,	neq, a, b) { return _ord(a, b) != ORD::EQ; };
//	TypeclassVirtual(VStar, min, a, b) { return _ord(a, b) == ORD::LT ? a : b; };
//	TypeclassVirtual(VStar, max, a, b) { return _ord(a, b) == ORD::GT ? a : b; };
//};



// Functor Class Template
template <typename A>
class Ordinal {
protected:
	template <class _ = A>
	inline static Function<ORD, A, A> _ord;
	template <class _ = A>
	inline static Function<bool, A, A> _lt;
	template <class _ = A>
	inline static Function<bool, A, A> _lte;
	template <class _ = A>
	inline static Function<bool, A, A> _gt;
	template <class _ = A>
	inline static Function<bool, A, A> _gte;
	template <class _ = A>
	inline static Function<bool, A, A> _eq;
	template <class _ = A>
	inline static Function<bool, A, A> _neq;
	template <class _ = A>
	inline static Function<A, A, A> _min;
	template <class _ = A>
	inline static Function<A, A, A> _max;

public:
	template <class _ = A>
	inline static auto ord = curry(Ordinal<A>::_ord<_>);
	template <class _ = A>
	inline static auto lt = curry(Ordinal<A>::_lt<_>);
	template <class _ = A>
	inline static auto lte = curry(Ordinal<A>::_lte<_>);
	template <class _ = A>
	inline static auto gt = curry(Ordinal<A>::_gt<_>);
	template <class _ = A>
	inline static auto gte = curry(Ordinal<A>::_gte<_>);
	template <class _ = A>
	inline static auto eq = curry(Ordinal<A>::_eq<_>);
	template <class _ = A>
	inline static auto neq = curry(Ordinal<A>::_neq<_>);
	template <class _ = A>
	inline static auto min = curry(Ordinal<A>::_min<_>);
	template <class _ = A>
	inline static auto max = curry(Ordinal<A>::_max<_>);
};

// Ordinal Base Instance
template <class A>
class BaseOrdinal {
protected:
	template <class _ = A>
	inline static Function<ORD, A, A> _ord;

	template <class _ = A>
	inline static auto _lt = [](A a, A b) -> bool {
		return Ordinal<A>::ord<_>(a)(b) == ORD::LT;
	};
	template <class _ = A>
	inline static auto _lte = [](A a, A b) -> bool {
		return Ordinal<A>::ord<_>(a)(b) != ORD::GT;
	};
	template <class _ = A>
	inline static auto _gt = [](A a, A b) -> bool {
		return Ordinal<A>::ord<_>(a)(b) == ORD::GT;
	};
	template <class _ = A>
	inline static auto _gte = [](A a, A b) -> bool {
		return Ordinal<A>::ord<_>(a)(b) != ORD::LT;
	};
	template <class _ = A>
	inline static auto _eq = [](A a, A b) -> bool {
		return Ordinal<A>::ord<_>(a)(b) == ORD::EQ;
	};
	template <class _ = A>
	inline static auto _neq = [](A a, A b) -> bool {
		return Ordinal<A>::ord<_>(a)(b) != ORD::EQ;
	};
	template <class _ = A>
	inline static auto _min = [](A a, A b) -> A {
		return Ordinal<A>::ord<_>(a)(b) == ORD::LT ? a : b;
	};
	template <class _ = A>
	inline static auto _max = [](A a, A b) -> A {
		return Ordinal<A>::ord<_>(a)(b) == ORD::GT ? a : b;
	};

public:
	template <class _ = A>
	inline static auto ord = curry(_ord<_>);
	template <class _ = A>
	inline static auto lt = curry(_lt<_>);
	template <class _ = A>
	inline static auto lte = curry(_lte<_>);
	template <class _ = A>
	inline static auto gt = curry(_gt<_>);
	template <class _ = A>
	inline static auto gte = curry(_gte<_>);
	template <class _ = A>
	inline static auto eq = curry(_eq<_>);
	template <class _ = A>
	inline static auto neq = curry(_neq<_>);
	template <class _ = A>
	inline static auto min = curry(_min<_>);
	template <class _ = A>
	inline static auto max = curry(_max<_>);
};
