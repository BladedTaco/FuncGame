#pragma once

#include "Types/Ord.h"

template <typename A>
class Number {
private:
	A _value;
	friend class Ordinal<Number<A>>;
public:
	Number(A value) { _value = value; }
	A get() { return _value; }
};

ORDINAL((A), Number<A>, (
	[](Number<A> a, Number<A> b) -> ORD {													PP__NEWLINE
		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;	PP__NEWLINE
	})
);
