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
public:
	template <typename B>
	inline static Function<Functor<B>, Arr<A, B>, Functor<A>> _fmap;
	template <typename B>
	inline static Function<Functor<B>, Arr<A, B>, Functor<A>> _map_replace_by;

public:
	template <typename B>
	inline static auto fmap = curry(Functor<A>::_fmap<B>);

	template <typename B>
	inline static auto map_replace_by = curry(Functor<A>::_map_replace_by<B>);


	
};

//
//namespace _Functor {
//	template <typename To, template <typename, typename...> class F, typename A, typename... Rest>
//	F<To, Rest...> a_fmap(Arr<A, To> f, F<A, Rest...> a) {
//		return Functor<F<A, Rest...>>::fmap<Arr<A, To>::to>(f)(a);
//	}
//};

// Functor Base Instance
template <template <class, class...> class F, typename A, typename... Rest>
class BaseFunctor {
protected:
	template <class B>
	inline static Function<F<B, Rest...>, Arr<A, B>, F<A, Rest...>> _fmap;
	
	template <class B>
	inline static auto _map_replace_by = [](A a, F<B, Rest...> f_b) -> F<A, Rest...> {
		Arr<B, A> f = { Prelude::constant<A, B>(a) };
		return Functor<F<B, Rest...>>::fmap<A>(f)(f_b);
	};
public:
	template <class B>
	inline static auto fmap = curry(_fmap<B>);
	template <class B>
	inline static auto map_replace_by = curry(_map_replace_by<B>);

	//TYPECLASS_FUNC_VPTR((B), fmap, ((Arr<A, B>), f), ((F<A, Rest...>), fa))
	template <class B> inline static auto v_fmap = curry([](void* f, void* fa) -> decltype(auto) { 
		return fmap<B>(*(Arr<A, B>*)f) (*(F<A, Rest...>*)fa);
	});
};
//
//
//class IFunctor {
//	inline static auto v_fmap = curry([](VStar f, VStar fa) -> VStar {
//
//		return fmap<B>(*(Arr<A, B>*)f) (*(F<A, Rest...>*)fa);
//	});
//};



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
