#pragma once

#include "Types/Ord.h"


//
//template <>
//class Ordinal<int> : protected BaseOrdinal<int>
//
//inline auto const BaseOrdinal<int>::ord = curry(BaseOrdinal<int>::_ord);
//
//inline auto const Ordinal<int>::_ord = [](int a, int b) -> ORD {
//	return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;
//};
//
//inline auto const Ordinal<int>::ord = curry(Ordinal<int>::_ord);

template <typename A>
class Number {
private:
	A _value;
	friend class Ordinal<Number<A>>;
public:
	Number(A value) : _value(value) {}
};


template <class A>
class Ordinal<Number<A>> : public BaseOrdinal<Number<A>> {
private:
	inline static auto _ord = [](Number<A> a, Number<A> b) -> ORD {
		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;
	};
public:
	inline static auto ord = curry(_ord);
};

//template <class A>
//class Ordinal<Number<A>> {
//private:
//	inline static auto _ord = [](Number<A> a, Number<A> b) -> ORD {
//		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;
//	};
//public:
//	inline static auto ord = curry(_ord);
//};

//
//template <class A> 
//class Ordinal<Number<A> > : public BaseOrdinal<Number<A> > { 
//private: 
//	inline static auto _ord = [](Number<A> a, Number<A> b) -> ORD { 
//		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT; 
//	}; 
//public: 
//	inline static auto ord = curry(_ord); 
//};
//;


//
//ORDINAL((A), Number<A>, (
//	[](Number<A> a, Number<A> b) -> ORD {
//		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;
//	})
//);
