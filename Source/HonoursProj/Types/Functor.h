#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

// Functor Instance Macro
#define FUNCTOR(TEMPLATES, INST, FMAP, MAP_REPLACE_BY)		 \
PP__DIRECTIVE(Typeclass, Functor, INST)						 \
TEMPLATE(UNBRACKET TEMPLATES)								 \
TYPECLASS_DEFN(Functor, TEMPLATES, INST) {					 \
	TYPECLASS_FUNC((B), fmap, FMAP)							 \
	TYPECLASS_OPT_FUNC((B), map_replace_by, MAP_REPLACE_BY)	 \
};

// Functor Class Template
template <typename A>
class Functor {
protected:
	template <typename B>
	inline static Function<Functor<B>, Function<B, A>, Functor<A>> _fmap;
	template <typename B>
	inline static Function<Functor<B>, Function<B, A>, Functor<A>> _map_replace_by;

public:
	template <typename B>
	inline static auto fmap = curry(Functor<A>::_fmap<B>);

	template <typename B>
	inline static auto map_replace_by = curry(Functor<A>::_map_replace_by<B>);

};

// Functor Base Instance
template <template <class> class F, typename A>
class BaseFunctor {
protected:
	template <class B>
	inline static Function<F<B>, Function<B, A>, F<A>> _fmap;
	
	template <class B>
	inline static auto _map_replace_by = [](A a, F<B> f_b) -> F<A> {
		Function<A, B> f = Prelude::constant<A, B>(a);
		return Functor<F<B>>::fmap<A>(f)(f_b);
	};
public:
	template <class B>
	//inline static Function<Function<F<B>, F<A>>, Function<B, A>> fmap = curry(_fmap<B>);
	inline static auto fmap = curry(_fmap<B>);
	template <class B>
	inline static auto map_replace_by = curry(_map_replace_by<B>);
};




//
//template <typename A> class Functor<Maybe <A>> : public BaseFunctor<Maybe, A> {
//private: template <typename B> inline static auto _fmap = [](Function<B, A> func, Maybe<A> f_a) -> Maybe<B> { if (f_a._isNothing) {
//	return Maybe<B>::Nothing();
//} else {
//	return Maybe<B>::Just(func(f_a._value));
//} }; public: template <typename B> inline static auto fmap = curry(_fmap <B>);
//};

//template<typename A> 
//class Functor<Maybe <A>> : public BaseFunctor<Maybe, A> {
//protected: 
//	template<typename B> inline static 
//		auto _fmap = [](Function<B, A> func, Maybe<A> f_a) -> Maybe<B> { 
//		if (f_a._isNothing) {
//			return Maybe<B>::Nothing();
//		} else {
//			return Maybe<B>::Just(func(f_a._value));
//		} 
//	};
//public: 
//	template<typename B> inline static 
//		auto fmap = curry(_fmap <B>); 
//};

//
//template <typename A>
//class Functor<Maybe<A>> : public BaseFunctor<Maybe, A> {
//private:
//	template <typename B>
//	inline static auto _fmap = [](std::function<B(A)> func, Maybe<A> f_a) -> Maybe<B> {
//		if (f_a._isNothing) {
//			return Maybe<B>::Nothing();
//		} else {
//			return Maybe<B>::Just(func(f_a._value));
//		}
//	};
//
//public:
//	template <class B>
//	inline static auto fmap = curry(_fmap<B>);
//};
//

//
//
// //Usage Example
//Maybe<int> a = Maybe<int>::Just(4);
//a = Functor<Maybe<int>>::fmap<int>([](int a) { return a * a; }, a);
//int q = Maybe<int>::fromMaybe(0, a);
//UE_LOG(LogTemp, Warning, TEXT("maybe %d"), q);
//
//a = Maybe<int>::Nothing();
//a = Functor<Maybe<int>>::fmap<int>([](int a) { return a * a; }, a);
//q = Maybe<int>::fromMaybe(0, a);
//UE_LOG(LogTemp, Warning, TEXT("maybe %d"), q);
