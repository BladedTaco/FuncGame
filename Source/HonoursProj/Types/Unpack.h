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


// Type Tuple Accessing
template <typename... Ts>
struct TyTuple {
	template <int idx>
	using get = typename std::tuple_element<idx, std::tuple<Ts...>>::type;
};


// Type Unwrapping
template <typename T>
struct unwrap_impl {
	using type = T;
};

template<template<typename> class E, typename T>
struct unwrap_impl<E<T>> {
	using type = T;
};

template<template<typename...> class E, typename... Ts>
struct unwrap_impl<E<Ts...>> {
	using type = TyTuple<Ts...>;
};

template<typename T>
using unwrap = typename unwrap_impl<T>::type;




// Testing
template <class...>
struct X;

static_assert(std::is_same_v< int, TyTuple<int, int>::get<0> >, "");
static_assert(std::is_same_v< unwrap<X<int, float>>::get<1>, float >, "");



// Tempalte Equality
template <template <typename...> class, template<typename...> class>
inline constexpr bool is_same_template = false;

template <template <typename...> class T>
inline constexpr bool is_same_template<T, T> = true;



template <class, template <class, class...> class>
struct is_instance : public std::false_type {};

template <class...Ts, template <class, class...> class U>
struct is_instance<U<Ts...>, U> : public std::true_type {};

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
typename std::enable_if_t< std::is_same_v<T, VStar>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::NONE);
}

template <class T>
typename std::enable_if_t< std::is_integral<T>::value, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::INT);
}


template <class T>
typename std::enable_if_t< std::is_floating_point<T>::value, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeBase::FLOAT);
}


template <class T>
typename std::enable_if_t< std::is_same_v<T, Number<unwrap<T>>>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeData::NUMBER, { FromType<unwrap<T>>() });
}

template <class T>
typename std::enable_if_t< std::is_same_v<T, Maybe<unwrap<T>>>, UTypeConst*>
FromType() {
	return UTypeConst::New(ETypeData::MAYBE, { FromType<unwrap<T>>() });
}

//template <class T,
//	typename std::enable_if_t< std::is_floating_point<T>::value, bool> = true
//>
//UTypeConst* FromType(T _) {
//	return UTypeConst::New(ETypeBase::FLOAT);
//}
//
//
//
////
////template <typename Inner>
////UTypeConst* FromType<Number<Inner>>() {
////	return UTypeConst::New(ETypeData::NUMBER, { FromType<Inner>() });
////}
//
//
//template <typename Wrap
//	, typename std::enable_if_t< std::is_same_v<Wrap, Number<unwrap<Wrap>>>, std::nullptr_t> = nullptr
//>
//UTypeConst* FromType(Wrap _) {
//	return UTypeConst::New(ETypeData::NUMBER, { FromType<unwrap<Wrap>>() });
//}
//
//
//template <typename Wrap
//	, typename std::enable_if_t< std::is_same_v<Wrap, Maybe<unwrap<Wrap>>>, std::nullptr_t> = nullptr
//>
//UTypeConst* FromType(Wrap _) {
//	return UTypeConst::New(ETypeData::MAYBE, { FromType<unwrap<Wrap>>() });
//}



//
//template <typename From, typename To>
//UTypeConst* FromType<Arr<From, To>>() {
//	return UTypeConst::New(ETypeData::FUNC, { FromType<From>(),  FromType<To>()});
//}


//template <class T, std::enable_if<std::is_same<unwrap<T>, T>::value, bool> = false>
//static constexpr UTypeConst* FromType() {
//	// Unwrap Type
//	using t = unwrap<T>;
//
//	// Test for Equality
//	if constexpr (is_instance<T, Number>::value) {
//		return UTypeConst::New(ETypeData::NUMBER, { FromType<t>() });
//	} else if constexpr (is_instance<T, Arr>::value) {
//		return UTypeConst::New(ETypeData::FUNC, { FromType<t::get<0>,  FromType<t::get<1> });
//	}
//
//	return NULL;
//}