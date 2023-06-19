
#include <functional>

template <typename Return, typename... Params>
using Function = std::function<Return(Params...)>;


//
//// https://stackoverflow.com/a/26768388
//template< class, class = std::void_t<> > struct
//needs_unapply : std::true_type {};
//
//template< class T > struct
//needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type {};
//
//template <typename F> 
//auto curry(F&& f) {
//  /// Check if f() is a valid function call. If not we need 
//  /// to curry at least one argument:
//	if constexpr (needs_unapply<decltype(f)>::value) {
//		return [=](auto&& x) {
//			return curry(
//				[=](auto&&...xs) -> decltype(f(x, xs...)) {
//				return f(x, xs...);
//			}
//			);
//		};
//	} else {
//	  /// If 'f()' is a valid call, just call it, we are done.
//		return f();
//	}
//}
//
 

//template <int N, typename F, typename... Args>
//auto curry(std::function<F> f, Args... args) {
//	return [](auto x) {
//		return curry<N - 1, F, auto, Args...>(f, args..., x);
//	}
//}
//
//template <int 0, typename F, typename... Args>
//auto curry(std::function<F> f, Args... args) {
//	return f(args...);
//}


//
//template<template<typename...> class F, int n, typename... OO>
//struct curry {
//	template<typename O> using Bind = curry<F, (n > 0) ? n - 1 : n, OO..., O>;
//};
//
//template<template<typename...> class F, typename... OO>
//struct curry<F, 0, OO...> {
//	using App = typename F<OO...>::App;
//	template<typename X> using Bind = typename App::template Bind<X>;
//};
//


//
//#include <type_traits>
//#include <map>
//
//template <template <class...> class C, class... T, class D = C<T...>>
//constexpr std::true_type valid(std::nullptr_t);
//
//template <template <class...> class C, class... T>
//constexpr std::false_type valid(...);
//
//template <class TrueFalse, template <class...> class C, class... ArgsSoFar>
//struct curry_impl;
//
//template <template <class...> class C, class... ArgsSoFar>
//struct curry_impl<std::true_type, C, ArgsSoFar...> {
//	using type = C<ArgsSoFar...>;
//};
//
//template <template <class...> class C, class... ArgsSoFar>
//struct curry_impl<std::false_type, C, ArgsSoFar...> {
//	template <class... MoreArgs>
//	using apply = curry_impl<decltype(valid<C, ArgsSoFar..., MoreArgs...>(nullptr)), C, ArgsSoFar..., MoreArgs...>;
//};
//
//template <template <class...> class C>
//struct curry {
//	template <class... U>
//	using apply = curry_impl<decltype(valid<C, U...>(nullptr)), C, U...>;
//};




/*******************************************************************************
 * This file is part of the "https://github.com/BlackMATov/kari.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2017-2023, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace kari_hpp
{
    template < typename F, typename... As >
    class curry_t;

    namespace impl
    {
        template < typename F >
        struct is_curried_impl
        : std::false_type {};

        template < typename F, typename... As >
        struct is_curried_impl<curry_t<F, As...>>
        : std::true_type {};
    }

    template < typename F >
    struct is_curried
    : impl::is_curried_impl<std::remove_cv_t<F>> {};

    template < typename F >
    inline constexpr bool is_curried_v = is_curried<F>::value;
}


namespace kari_hpp
{
    template < typename F, typename... Args >
    class curry_t final {
    public:
        constexpr curry_t(F f)
        : f_(std::move(f)) {}

        constexpr curry_t(F f, std::tuple<Args...> args)
        : f_(std::move(f))
        , args_(std::move(args)) {}

        constexpr auto operator()() && {
            return detail::curry_or_apply(
                std::move(f_),
                std::move(args_));
        }

        template < typename A >
        constexpr auto operator()(A&& a) && {
            return detail::curry_or_apply(
                std::move(f_),
                std::tuple_cat(
                    std::move(args_),
                    std::make_tuple(std::forward<A>(a))));
        }

        template < typename A, typename... As >
        constexpr auto operator()(A&& a, As&&... as) && {
            return std::move(*this)(std::forward<A>(a))(std::forward<As>(as)...);
        }

        template < typename... As >
        constexpr auto operator()(As&&... as) const & {
            return std::move(curry_t(*this))(std::forward<As>(as)...);
        }
    private:
        F f_;
        std::tuple<Args...> args_;
    };
}

namespace kari_hpp
{
    template < typename F >
    constexpr auto curry(F&& f) {
        if constexpr ( is_curried_v<std::decay_t<F>> ) {
            return std::forward<F>(f);
        } else {
            return detail::curry_or_apply(std::forward<F>(f), {});
        }
    }

    template < typename F, typename A, typename... As >
    constexpr auto curry(F&& f, A&& a, As&&... as) {
        return curry(std::forward<F>(f))(std::forward<A>(a), std::forward<As>(as)...);
    }
}


















// Prelude functions
namespace Prelude {
	template <typename A, typename B>
	A constant(A a, B b) {
		return a;
	}

	template <typename A, typename B, typename C, typename F>
	C compose(Function<C, B> f, Function<B, A> g, A x) {
		return f(g(x));
	}
}

// Functor Class Template
template <typename A>
class Functor {
public:
	template <typename B>
	static Functor<B> fmap(std::function<B(A)> func, Functor<A> f_a) = 0;
};

template <template <class> class F, class A>
class BaseFunctor {
public:
	template <class B>
	static F<A> map_replace_by(A a, F<B> f_b) {
		auto cf = kari_hpp::curry(Prelude::constant<A, B>);
		return Functor<F<B>>::fmap<A>(cf(a), f_b);
	}
};


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
	static A fromMaybe(A fallback, Maybe<A> maybe_a) {
		if (maybe_a._isNothing) {
			return fallback;
		} else {
			return maybe_a._value;
		}
	}
};





template <typename A>
class Functor<Maybe<A>> : public BaseFunctor<Maybe, A> {
public:
	template <typename B>
	static Maybe<B> fmap(std::function<B(A)> func, Maybe<A> f_a) {
		if (f_a._isNothing) {
			return Maybe<B>::Nothing();
		} else {
			return Maybe<B>::Just(func(f_a._value));
		}
	}
};



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
