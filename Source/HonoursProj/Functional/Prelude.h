// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Ensure Preprocessed Files aren't 60k lines long
#ifndef PP__PREPROCESSING
#include <functional>
#include "Functional/curry_gen.h"
#else
include <functional>
include "Functional/curry_gen.h"
#endif


//
//// Function Shorthand
//template <typename Return, typename... Params>
//using Function = std::function<Return(Params...)>;
//
//// Curried Function Shorthand
//template <typename To, typename From>
//class Func;
//
//// Curried Function Shorthand as Arrow From -> To
//template <typename From, typename To>
//using Arr = Func<To, From>;


//template <typename From, typename To, typename... Rest>
//
//
//using Arrs = Arr<From, Arrs<To, Rest...>>;
//template <typename From, typename To>
//using Arrs = Arr<From, To>;
//



//
//// Function Currying (https://stackoverflow.com/a/26768388)
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
//		// take an argument
//		return [=](auto&& x) {
//			// return curried rest of function with first arugment applied
//			return curry(
//				[=](auto&&...xs) -> decltype(f(x, xs...)) {
//					return f(x, xs...);
//				}
//			);
//		};
//	} else {
//	  /// If 'f()' is a valid call, just call it, we are done.
//		return f();
//	}
//}



//
////template <typename F>
//template <typename To, typename First, typename... Rest>
//auto curry(Function<To, First, Rest...>&& f) {
//  /// Check if f() is a valid function call. If not we need 
//  /// to curry at least one argument:
//	if constexpr (needs_unapply<decltype(f)>::value) {
//		// take an argument
//		auto ret = [=](First&& x) {
//			// return curried rest of function with first arugment applied
//			return curry(
//				[=](auto&&...xs) -> decltype(f(x, xs...)) {
//					return f(x, xs...);
//				}
//			);
//		};
//		return Arr<First, decltype(ret((First)0))>(ret);
//	} else {
//	  /// If 'f()' is a valid call, just call it, we are done.
//		return f();
//	}
//}

//template <typename F>
//auto curry(Function<To, First, Rest...>&& f) {
//  /// Check if f() is a valid function call. If not we need 
//  /// to curry at least one argument:
//	if constexpr (needs_unapply<decltype(f)>::value) {
//		// take an argument
//		auto ret = [=](First&& x) {
//			// return curried rest of function with first arugment applied
//			return curry(
//				[=](auto&&...xs) -> decltype(f(x, xs...)) {
//				return f(x, xs...);
//			}
//			);
//		};
//		return Arr<First, decltype(ret(( First )0))>(ret);
//	} else {
//	  /// If 'f()' is a valid call, just call it, we are done.
//		return f();
//	}
//}










//#include <algorithm>
//#include <functional>
//#include <iostream>
//#include <typeinfo>
// 
// 




// Prelude functions
namespace Prelude {
	// Constant a b = a
	template <typename A, typename B>
	auto constant = curry([](A a, B b) -> A {
		return a;
	});

	// compose f g = \ x -> f (g x)
	template <typename A, typename B, typename C>
	auto compose = curry([](Arr<B, C> f, Arr<A, B> g, A x) -> C {
		return f(g(x));
	});

	template <typename A>
	auto id = curry([](A a) -> A { return a; });

	template <typename A, typename B>
	auto swap = curry([](TTuple<A, B> tup) -> TTuple<B, A> {
		return MakeTuple(tup.template Get<1>(), tup.template Get<0>());
	});
};