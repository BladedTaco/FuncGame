#pragma once

#include "Types/Ord.h"



#ifndef PP__PREPROCESSING

#include "Types/VStar.h"

#else

include "Types/VStar.h"

#endif

#include "Types/FDecl.h"





#define InlineStaticConstStruct(T, NAME, ...) \
static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()

class INumber {
public:
	class Ordinal : public virtual IOrdinal {
	private:
		virtual ORD _ord(VStar me, VStar other) const override { return ORD::LT; }
	public:
		Ordinal() = default;
	};

	inline static const Ordinal POrdinal = {};

public:
	InlineStaticConstStruct(Typeclass, Instances,
		$.Ordinal = &INumber::POrdinal
	);
};











template <typename A>
class Number : public virtual INumber {
private:
	A _value;
	friend class ::Ordinal<Number<A>>;
public:
	Number(A value) : _value(value) {}
	A get() const { return _value; }
};

template <>
class Number<VStar> : public virtual INumber {
private:
	VStar _value;
	friend class ::Ordinal<NumberV>;
public:
	template <typename A>
	Number(A value)
		: _value(value) {};

	template <typename A>
	const A* get() const { return _value.GetUnsafePtr<A>(); }

	// Copy Construction
	template <typename A>
	Number(const Number<A>& other) 
		: _value(other.get()) {}

	// Copy Constructor for NumberVs
	template <>
	Number(const NumberV& other)
		: _value(other._value) {};

	Number(const NumberV& other) {
		_value = other._value;
	};


	// Move Constructor is move into container
	Number(NumberV&& other) {
		_value = VStar(other);
	}
};



//
//class INumber {
//public:
//	static class Ordinal : public virtual IOrdinal {
//	private:
//		virtual ORD _ord(VStar me, VStar other) const override { return ORD::EQ; }
//	} POrdinal;
//
//};

//class INumber::Ordinal : public virtual IOrdinal {
//private:
//	virtual ORD _ord(VStar me, VStar other) const override { return ORD::EQ; }
//};



ORDINAL((A), Number, (
	[](Number<A> a, Number<A> b) -> ORD {													PP__NEWLINE
		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;	PP__NEWLINE
	})
);



//ORDINAL((), NumberV, (
//	[](Number<A> a, Number<A> b) -> ORD {													PP__NEWLINE
//	return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;	PP__NEWLINE
//})
//);

//template <>
//class Ordinal<int> : public BaseOrdinal<int> {
//private:
//	template <class A>
//	inline static auto _ord = [](int a, int b) -> ORD {
//		return *a.get<A>() == *b.get<A>()
//			? ORD::EQ
//			: *a.get<A>() < *b.get<A>()
//			? ORD::LT
//			: ORD::GT;
//	};
//public:
//	template <class A>
//	inline static auto ord = curry(_ord<A>);
//};
//

template <>
class Ordinal<NumberV> : public BaseOrdinal<NumberV> {
private: 
	template <class A> 
	inline static auto _ord = [](NumberV* a, NumberV* b) -> ORD {
		float v0, v1;
		if (a->_value.ValidCast<int>()) {
			v0 = *a->get<int>();
			v1 = *b->get<int>();
		} else if (a->_value.ValidCast<float>()) {
			v0 = *a->get<float>();
			v1 = *b->get<float>();
		} else { return ORD::EQ; }

		return v0 == v1
			? ORD::EQ 
			: v0 < v1
				? ORD::LT 
				: ORD::GT;
	}; 
public:
	template <class A> 
	inline static auto ord = curry(_ord<A>);
};