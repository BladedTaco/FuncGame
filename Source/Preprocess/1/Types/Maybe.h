#pragma once

#include "Types/Functor.h"

#include "Types/FDecl.h"


// Functor Maybe
template <typename A>
class Maybe : public Functor<Maybe<A>> {
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

//
//template <>
//class Maybe<VStar> {
//private:
//	bool _isNothing;
//	VStar _value;
//	Maybe() {
//		_isNothing = true;
//	}
//	template <typename A>
//	Maybe(A a) {
//		_isNothing = false;
//		_value = VStar(a);
//	}
//	friend class Functor<Maybe<VStar>>;
//public:
//	template <typename A>
//	static Maybe<VStar> Just(A a) {
//		return Maybe(a);
//	}
//	static Maybe<VStar> Nothing() {
//		return Maybe();
//	}
//
//	template <typename OtherInner>
//	Maybe(Maybe<OtherInner>& other) {
//		_isNothing = other._isNothing;
//		_value = VStar(other._value);
//	}
//
//	template <>
//	Maybe(Maybe<VStar>& other) 
//		: _value(other._value)
//		, _isNothing(other._isNothing) {};
//public:
//	template <typename A>
//	A fromMaybe(A fallback) {
//		if (_isNothing) {
//			return fallback;
//		} else {
//			return _value.Get<A>();
//		}
//	}
//};


//
//class IMaybe {
//private:
//	bool _isNothing;
//	VStar _value;
//	IMaybe() {
//		_isNothing = true;
//	}
//	template <typename A>
//	IMaybe(A a) {
//		_isNothing = false;
//		_value = a;
//	}
//	friend class Functor<Maybe<VStar>>;
//public:
//	static Maybe<A> Just(A a) {
//		return Maybe<A>(a);
//	}
//	static Maybe<A> Nothing() {
//		return Maybe<A>();
//	}
//public:
//	A fromMaybe(A fallback) {
//		if (_isNothing) {
//			return fallback;
//		} else {
//			return _value;
//		}
//	}
//
//	Maybe<class VStar> Void() {
//
//	}
//};


template <typename A>
auto fromMaybe = curry([](A a, Maybe<A> m_a) -> A {
	return m_a.fromMaybe(a);
});


FUNCTOR((A), Maybe, (
	[](Arr<A, B> func, Maybe<A> f_a) -> Maybe<B> {		PP__NEWLINE
		if (f_a._isNothing) {						    PP__NEWLINE
			return Maybe<B>::Nothing();				    PP__NEWLINE
		} else {									    PP__NEWLINE
			return Maybe<B>::Just(func(f_a._value));    PP__NEWLINE
		}												PP__NEWLINE
	}), 
	()
);
