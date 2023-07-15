#pragma once


#ifndef PP__PREPROCESSING

#include <memory>
#include <type_traits>

#include "Types/Type.h"
#include "Types/Types_gen.h"

#else 

include <memory>
include <type_traits>

include "Types/Type.h"
include "Types/Types_gen.h"

#endif

#include "Types/FDecl.h"

// Testing
template <class...>
struct X;



template <typename A, typename>
using to_first = A;

// Type Tuple Accessing
template <typename... Ts>
struct TyTuple {
	template <int idx>
	using get = typename std::tuple_element<idx, std::tuple<Ts..., std::false_type, std::false_type, std::false_type>>::type;

	template <template <typename...> typename T>
	using rewrap = T<Ts...>;

	inline static constexpr int size = sizeof...(Ts);
};

// Type Tuple Accessing
template <>
struct TyTuple<std::false_type> {
	template <int idx>
	using get = std::false_type;

	template <template <typename...> typename T>
	using rewrap = std::false_type;

	inline static constexpr int size = 0;
};

template <typename With, typename... Replace>
using replace = TyTuple<to_first<With, Replace>...>;



// Recursive Tuple Operations
template <int Num, template <int> typename F>
struct Recurse {
	template <typename... Rest>
	using R = TyTuple<F<Num>, Rest...>;

	using result = typename Recurse<Num - 1, F>::result::template rewrap<R>;
};

template <template <int> typename F>
struct Recurse<0, F> {
	using result = TyTuple<F<0>>;
};

template <template <int> typename F>
struct Recurse<-1, F> {
	using result = TyTuple<>;
};


template <typename T>
struct FlipTuple_t {
	using type = typename Recurse<T::size - 1, typename T::template get>::result;
};

template <>
struct FlipTuple_t<std::false_type> {
	using type = TyTuple<>;
};

// Flip A TyTuple
template <typename T>
using FlipTuple = typename FlipTuple_t<T>::type;
//using FlipTuple = typename Recurse<T::size - 1, typename T::template get>::result;

// Take n elements from a TyTuple
template <int N, typename T>
using take_n = FlipTuple<typename Recurse<N - 1, typename T::template get>::result>;


// Type Unwrapping for unwrappable type
template <typename T>
struct unwrap_impl : std::false_type {
	using wrapper = std::false_type;
	using wrapper_fill = std::false_type;

	using types = TyTuple<std::false_type>;
	template <typename A>
	using is_only = std::false_type;
};


// Type Unwrapping for wrapped type
template<template<typename...> class E, typename... Ts>
struct unwrap_impl<E<Ts...>> : std::true_type {

	template <typename... Rewrap>
	using wrapper = E<Rewrap...>;

	template <typename Rewrap>
	using wrapper_fill = typename replace<Rewrap, Ts...>::template rewrap<E>;


	using types = TyTuple<Ts...>;
	template <typename A>
	using is_only = typename std::is_same< types, replace<A, Ts...> >;
};

// Type Unwrapping for wrapped type
template<template<typename> class E, typename T>
struct unwrap_impl<E<T>> : std::true_type {
	template <typename Rewrap>
	using wrapper = E<Rewrap>;
	template <typename Rewrap>
	using wrapper_fill = E<Rewrap>;
	using types = TyTuple<T>;
	template <typename A>
	using is_only = typename std::is_same< types, replace<A, T> >;
};

template<typename T>
using unwrap = typename unwrap_impl<T>::types;

template<typename T, int idx>
using extract = typename unwrap_impl<T>::types::template get<idx>;

template<typename T, template <typename...> typename Wrapper>
using rewrap = typename unwrap_impl<T>::types::template rewrap<Wrapper>;

template<int N, typename T, template <typename...> typename Wrapper>
using rewrap_cut = typename take_n<N, typename unwrap_impl<T>::types>::template rewrap<Wrapper>;

template<typename T, typename... NewInner>
using repack = typename unwrap_impl<T>::template wrapper<NewInner...>;



template<typename T, typename NewInner>
using repack_fill = typename unwrap_impl<T>::template wrapper_fill<NewInner>;

static_assert(std::is_same_v<  repack_fill<X<int, float>, char>, X<char, char> >, "");


template <typename T, typename Inner>
using contains_only = typename unwrap_impl<T>::template is_only<Inner>;


static_assert(contains_only<X<VStar, VStar>, VStar>::value, "");
static_assert(!contains_only<X<VStar, int>, VStar>::value, "");

template <typename T>
struct is_template_t : std::is_base_of< std::true_type, unwrap_impl<T> > {};

template <typename T>
struct not_template_t : std::is_base_of< std::false_type, unwrap_impl<T> > {};
//
//template<typename T>
//inline constexpr bool is_template = is_template_t<T>::value;

template<typename T>
using is_template = typename is_template_t<T>::value;

template<typename T>
using not_template = typename not_template_t<T>::value;
//
//template<typename T>
//inline constexpr bool not_template = not_template_t<T>::value;



static_assert(std::is_same_v< int, TyTuple<int, int>::get<0> >, "");
static_assert(std::is_same_v< unwrap<X<int, float>>::get<1>, float >, "");

static_assert(std::is_same_v< repack<X<int, float>, int, float>, X<int, float> >, "");
//static_assert(std::is_same_v< repack<X<int, float>, int, int>, X<int, float> >, "fails");

static_assert(std::is_same_v< repack<X<int, float>, int, float>, unwrap<X<int, float>>::rewrap<X> >, "");


template <typename T, typename U>
inline constexpr bool is_similar = std::is_same<std::remove_const_t<std::remove_reference_t<T>>, U>::value;


static_assert(is_similar<const int&, int>, "");
static_assert(!is_similar<const float&, int>, "");


//
//template <typename Inst>
//struct is_instance_t {};
//
//template <class T, template <class, class...> class U>
//struct is_instance_t<std::true_type> : std::is_same<T, unwrap<T>::rewrap<U> > {};


//
//template <bool Test, class T, template <class, class...> class U>
//struct is_instance_t;
//
//
//template <class T, template <class, class...> class U>
//struct is_instance_t<false, T, U> : std::false_type {};
//
//template <class T, template <class, class...> class U>
//struct is_instance_t<true, T, U> : typename std::is_same<T, unwrap<T>::rewrap<U> > {};

//
//template <class T, template <class, class...> class U>
//inline constexpr bool is_instance = is_template<T> && std::is_same_v<T, unwrap<T>::rewrap<U> >;
//
//
//template <class T, class U>
//inline constexpr bool is_instance_i = false;
//template <class T>
//inline constexpr bool is_instance_i<T, T> = true;
//
//template <class T, template <class, class...> class U>
//inline constexpr bool is_instance = typename is_instance_i< T, unwrap<T>::rewrap<U> >;


template <class T, template <class, class...> class U>
using is_instance_t = typename std::is_same<T, rewrap<T, U> >;
//
//template <class T, template <class, class...> class U>
//inline constexpr bool is_instance = is_instance_t<T, U>::value;


template <class T, template <class, class...> class U>
inline constexpr bool is_instance = is_similar<T, rewrap<T, U> >;
//
//template <int N, class T, template <class, class...> class U>
//inline constexpr bool is_instance_n = std::is_same_v<T, rewrap_cut<N, T, U> >;


template <int N, class T, template <class, class...> class U>
inline constexpr bool is_instance_n = []() {
	if constexpr (unwrap<T>::size == N) {
		return is_similar<T, rewrap_cut<N, T, U> >;
	}
	return false;
}();

//template <class T, template <class, class...> class U>
//using is_instance = is_instance_t<T, U>::value;
//
//
//template <class T, template <class, class...> class U>
//inline constexpr bool is_instance = typename is_instance_t<is_template_t<T>, T, U>::value;

static_assert(!is_instance_n<2, X<int>, X>, "");
static_assert(is_instance_n<2, X<int, int>, X>, "");
static_assert(!is_instance_n<2, X<int, int, int>, X>, "");

static_assert(!is_instance<int, Number>, "");
static_assert(is_instance<Number<int>, Number>, "");
static_assert(is_instance<Number<X<int>>, Number>, "");


static_assert(is_instance<Number<int>, Number>, "");

static_assert(is_template_t<X<int, float>>::value, "");


//static_assert(is_instance<Number<int>, X>, "");


//
//template <class T,
//	typename std::enable_if_t< std::is_integral<T>::value, bool> = true
//>
//UTypeConst* FromType(T _) {
//	return UTypeConst::New(ETypeBase::INT);
//}
//
//template <class T,
//	typename std::enable_if_t< std::is_floating_point<T>::value, bool> = true
//>
//UTypeConst* FromType(T _) {
//	return UTypeConst::New(ETypeBase::FLOAT);
//}

class VStar;

// TODOODODODOOD;
template <class T>
typename std::enable_if_t< is_similar<T, VStar>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::NONE);
};


template <class T>
typename std::enable_if_t< is_similar<T, Bool>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::BOOL);
};

template <class T>
typename std::enable_if_t< is_similar<T, int>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::INT);
};


template <class T>
typename std::enable_if_t< is_similar<T, float>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::FLOAT);
};


template <class T>
typename std::enable_if_t< is_instance_n<1, T, Number>, UTypeConst*>
FromType() {
	using T_0 = extract<T, 0>;
	return UTypeConst::New(ETypeData::NUMBER, { FromType<T_0>() });
};

template <class T>
typename std::enable_if_t< is_instance_n<1, T, Maybe>, UTypeConst*>
FromType() {
	using T_0 = extract<T, 0>;
	return UTypeConst::New(ETypeData::MAYBE, { FromType<T_0>() });
};

template <class T>
typename std::enable_if_t< is_instance_n<2, T, Func>, UTypeConst*>
FromType() {
	using From = extract<T, 1>;
	using To = extract<T, 0>;
	return UTypeConst::New(ETypeData::FUNC, { FromType<From>(), FromType<To>() });
};

