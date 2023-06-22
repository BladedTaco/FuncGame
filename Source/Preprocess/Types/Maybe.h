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
	[](Function<B, A> func, Maybe<A> f_a) -> Maybe<B> {
		if (f_a._isNothing) {
			return Maybe<B>::Nothing();
		} else {
			return Maybe<B>::Just(func(f_a._value));
		}
	}), 
	()
);
