#pragma once

#include "Types/Functor.h"

// Functor Maybe
template <typename A>
class Maybe {
private:
	bool _isNothing;
	A _value;
	Maybe() {
		_isNothing = true;
		_value = false;
	}
	Maybe(A a) {
		_isNothing = false;
		_value = a;
	}
	friend class Functor<Maybe<A>>;
public:
	static Maybe<A> Just(A a) {
		return Maybe<A>(a);
	}
	static Maybe<A> Nothing() {
		return Maybe<A>();
	}
public:
	A fromMaybe(A fallback) {
		if (_isNothing) {
			return fallback;
		} else {
			return _value;
		}
	}
};

template <typename A>
auto fromMaybe = curry([](A a, Maybe<A> m_a) -> A {
	return m_a.fromMaybe(a);
});


FUNCTOR((A), Maybe, (
	[](Arr<A, B> func, Maybe<A> f_a) -> Maybe<B> { PP__NEWLINE
		if (f_a._isNothing) {						    PP__NEWLINE
			return Maybe<B>::Nothing();				    PP__NEWLINE
		} else {									    PP__NEWLINE
			return Maybe<B>::Just(func(f_a._value));    PP__NEWLINE
		}												PP__NEWLINE
	}), 
	()
);
