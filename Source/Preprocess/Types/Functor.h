#pragma once

#include "MacroUtils.h"

// test

#if __INTELLISENSE__
#include <functional>
#endif

#ifndef __PREPROCESSING
#include <functional>
#else
include <functional>
#endif


template <typename Return, typename... Params>
using Function = std::function<Return(Params...)>;


template< class, class = std::void_t<> > struct
needs_unapply : std::true_type {};

template< class T > struct
needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type {};


template <typename F> 
auto curry(F&& f) {
  /// Check if f() is a valid function call. If not we need 
  /// to curry at least one argument:
    if constexpr (needs_unapply<decltype(f)>::value) {
        return [=](auto&& x) {
            return curry(
                [=](auto&&...xs) -> decltype(f(x, xs...)) {
                return f(x, xs...);
            }
            );
        };
    } else {
      /// If 'f()' is a valid call, just call it, we are done.
        return f();
    }
}



// Prelude functions
namespace Prelude {
	// Constant a b = a
	template <typename A, typename B>
	auto constant = curry([](A a, B b) -> A {
		return a;
	});

	// compose f g = \ x -> f (g x)
	template <typename A, typename B, typename C>
	auto compose = curry([](Function<C, B> f, Function<B, A> g, A x) -> C {
		return f(g(x));
	});
	// compose f g = \ x -> f (g x)
	//template <typename A, typename B, typename C>
	//auto compose = curry([](Function<C, B> f, Function<B, A> g) -> Function<C, A> {
	//	return std::bind(f, std::bind(g, std::placeholders::_1));
	//});
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


#define _TEMPLATE_LOOP(A) , typename A
#define TEMPLATE(...) NULLARY( (template <MAP_LIST(_TEMPLATE_LOOP, __VA_ARGS__)>), (), __VA_ARGS__)
#define _LIST_LOOP(A) , A
#define TEMPLATE_INST(...) NULLARY( (<MAP_LIST(_LIST_LOOP, __VA_ARGS__)>), (), __VA_ARGS__)



#define FUNC_DEFN(TEMPLATES, FUNCNAME, DEFN)	\
TEMPLATE(UNBRACKET TEMPLATES)					\
inline static auto FUNCNAME = UNBRACKET DEFN;


#define CURRY_DEFN(TEMPLATES, FUNCNAME) FUNC_DEFN(TEMPLATES, FUNCNAME, (curry(_##FUNCNAME TEMPLATE_INST( UNBRACKET TEMPLATES))))


#define TYPECLASS_FUNC(TEMPLATES, FUNCNAME, DEFN)	\
private:											\
	FUNC_DEFN(TEMPLATES, _## FUNCNAME, DEFN)		\
public:												\
	CURRY_DEFN(TEMPLATES, FUNCNAME)


#define TYPECLASS_OPT_FUNC(TEMPLATES, FUNCNAME, DEFN) NULLARY((TYPECLASS_FUNC(TEMPLATES, FUNCNAME, DEFN)), (), UNBRACKET DEFN)

#define TYPECLASS_DEFN(CLS, TEMPLATES, INSTANCE) class CLS<INSTANCE TEMPLATE_INST(UNBRACKET TEMPLATES)> : public Base##CLS<INSTANCE, UNBRACKET TEMPLATES>


#define FUNCTOR(TEMPLATES, INST, FMAP, MAP_REPLACE_BY)		\
TEMPLATE(UNBRACKET TEMPLATES)								\
TYPECLASS_DEFN(Functor, TEMPLATES, INST) {					\
	TYPECLASS_FUNC((B), fmap, FMAP)							\
	TYPECLASS_OPT_FUNC((B), map_replace_by, MAP_REPLACE_BY)	\
};


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

auto a = Prelude::constant<int, float>(1);

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
