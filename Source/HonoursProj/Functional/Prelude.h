// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Ensure Preprocessed Files aren't 60k lines long
#ifndef __PREPROCESSING
#include <functional>
#else
include <functional>
#endif

// Function Shorthand
template <typename Return, typename... Params>
using Function = std::function<Return(Params...)>;


// Function Currying (https://stackoverflow.com/a/26768388)
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

};