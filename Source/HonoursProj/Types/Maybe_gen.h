﻿// ---------------------------------------------------------------------------------------
// This File (Maybe_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Functor.h"
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

 /*Added Typeclass Functor Instance Maybe*/ 
 template <class A> 
 class Functor<Maybe <A> > : public BaseFunctor<Maybe,A> { 
 private: 
 template <class B> 
 inline static auto _fmap = [](Function<B, A> func, Maybe<A> f_a) -> Maybe<B> { 
 if (f_a._isNothing) { 
 return Maybe<B>::Nothing(); 
 } else { 
 return Maybe<B>::Just(func(f_a._value)); 
 } 
 }; 
 public: 
 template <class B> 
 inline static auto fmap = curry(_fmap<B>); 
 };
;
