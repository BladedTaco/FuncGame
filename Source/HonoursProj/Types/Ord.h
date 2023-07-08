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







class IOrdinal {
private:
	virtual ORD		_ord(VStar me, VStar other)	const = 0;
	virtual bool	_lt(VStar me, VStar other)	const { return _ord(me, other) == ORD::LT; }
	virtual bool	_lte(VStar me, VStar other) const { return _ord(me, other) != ORD::GT; }
	virtual bool	_gt(VStar me, VStar other)	const { return _ord(me, other) == ORD::GT; }
	virtual bool	_gte(VStar me, VStar other) const { return _ord(me, other) != ORD::LT; }
	virtual bool	_eq(VStar me, VStar other)	const { return _ord(me, other) == ORD::EQ; }
	virtual bool	_neq(VStar me, VStar other) const { return _ord(me, other) != ORD::EQ; }
	virtual VStar	_min(VStar me, VStar other) const { return _ord(me, other) == ORD::LT ? me : other; }
	virtual VStar	_max(VStar me, VStar other) const { return _ord(me, other) == ORD::GT ? me : other; }

public:

	//template <typename Func>
	//auto resolve() {
	//	return this->*Func;
	//}

	//const auto ord = fcurry(std::function<ORD(VStar, VStar)>(this->*_ord));


	//const auto ord = curry([this](VStar a, VStar b) { return this->_ord(a, b); });

	const auto ord	() const { return curry([this](VStar a, VStar b) { return this->_ord(a, b); }); };

	template <typename Singleton>
	inline static const auto t_ord = curry([](VStar a, VStar b) { return Singleton::Get()->_ord(a, b); });

	inline static const auto c_ord = curry([](IOrdinal* cls, VStar a, VStar b) { return cls->_ord(a, b); });


public:
	//inline static const auto ord = c_ord(NULL);


	virtual auto ord(VStar p1) -> decltype(c_ord(this)(p1)) { return c_ord(this)(p1); };
	virtual auto ord() -> decltype(c_ord(this)) { return c_ord(this); };



	//template <class = void*>
	//inline static const auto ord = curry(this->_ord);

	//constexpr auto lt	(IOrdinal* ptr) { return curry(ptr->_lt); }
	//constexpr auto lte	(IOrdinal* ptr) { return curry(ptr->_lte); }
	//constexpr auto gt	(IOrdinal* ptr) { return curry(ptr->_gt); }
	//constexpr auto gte	(IOrdinal* ptr) { return curry(ptr->_gte); }
	//constexpr auto eq	(IOrdinal* ptr) { return curry(ptr->_eq); }
	//constexpr auto neq	(IOrdinal* ptr) { return curry(ptr->_neq); }
	//constexpr auto min	(IOrdinal* ptr) { return curry(ptr->_min); }
	//constexpr auto max	(IOrdinal* ptr) { return curry(ptr->_max); }
};

// A Static Singleton Class
template <typename Of>
class Singleton {
private:
	Singleton() {}
	friend class Of;
public:
	void operator=(Singleton const&) = delete;
	Singleton(Singleton const&) = delete;

public:
	const Of* const operator->() const {
		return Get();
	}
	static Of* const Get() {
		static Of Instance;
		return &Instance;
	}
};


class NumberOrdinal : public virtual IOrdinal, public virtual Singleton<NumberOrdinal> {
private:
	virtual ORD _ord(VStar me, VStar other) const override { return ORD::LT; }
public:

	inline static const auto ord = curry([](VStar a, VStar b) { return Get()->_ord(a, b); });


	inline static const auto vord = IOrdinal::ord<NumberOrdinal>;

	const auto ord() const { return curry([this](VStar a, VStar b) { return NumberOrdinal::Get()->_ord(a, b); }); };
};






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
