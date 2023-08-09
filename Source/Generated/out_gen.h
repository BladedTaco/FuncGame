#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"
#pragma once

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Show.h"
#pragma once

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"


#pragma once
#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\HonoursProj\\LoopMacros.h"


#pragma once














































































































































































































#line 5 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"
















































































































































































   









#line 4 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Show.h"

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Functional/Prelude.h"


#pragma once






include <functional>
include "Functional/curry_gen.h"
#line 13 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Functional/Prelude.h"
























































































































namespace Prelude {
	
	template <typename A, typename B>
	auto constant = curry([](A a, B b) -> A {
		return a;
	});

	
	template <typename A, typename B, typename C>
	auto compose = curry([](Arr<B, C> f, Arr<A, B> g, A x) -> C {
		return f(g(x));
	});

	template <typename A>
	auto id = curry([](A a) -> A { return a; });

	template <typename A, typename B>
	auto swap = curry([](TTuple<A, B> tup) -> TTuple<B, A> {
		return MakeTuple(tup.Get<1>(), tup.Get<0>());
	});
};
#line 6 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Show.h"
#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Functional/Typeclass.h"
#pragma once

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Preprocess/Include.h"
#pragma once














#line 17 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Preprocess/Include.h"






#line 4 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Functional/Typeclass.h"





































































































#line 7 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Show.h"

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Unpack.h"
#pragma once












include <memory>
include <type_traits>

include "Types/Type.h"
include "Types/Types_gen.h"

#line 21 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Unpack.h"

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/FDecl.h"
#pragma once




class VStar;


template <class T> class Number;
template <class T> class Maybe;
class Bool;

template <class From, class To> class Func;


template <> class Number<VStar>;
template <> class Maybe<VStar>;

template <typename To> class Func<To, VStar>;



typedef  Number<VStar>  NumberV;
typedef  Maybe<VStar>  MaybeV;

typedef Func<VStar, VStar> ArrV;



template <typename From, typename To>
using Arr = Func<To, From>;



class IOrdinal;
class IFunctor;
class IShow;



struct Typeclass {
	const IOrdinal* Ordinal;
	const IFunctor* Functor;
	const IShow* Show;
};


class ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const = 0;
public:
	const Typeclass* GetTypeclass() const { return _GetTypeclass(); };
};
#line 23 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Unpack.h"


template <class...>
struct X;



template <typename A, typename>
using to_first = A;


template <typename... Ts>
struct TyTuple {
	template <int idx>
	using get = typename std::tuple_element<idx, std::tuple<Ts..., std::false_type, std::false_type, std::false_type>>::type;

	template <template <typename...> typename T>
	using rewrap = T<Ts...>;

	inline static constexpr int size = sizeof...(Ts);
};


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


template <typename T>
using FlipTuple = typename FlipTuple_t<T>::type;



template <int N, typename T>
using take_n = FlipTuple<typename Recurse<N - 1, typename T::template get>::result>;



template <typename T>
struct unwrap_impl : std::false_type {
	using wrapper = std::false_type;
	using wrapper_fill = std::false_type;

	using types = TyTuple<std::false_type>;
	template <typename A>
	using is_only = std::false_type;
};



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




template<typename T>
using is_template = typename is_template_t<T>::value;

template<typename T>
using not_template = typename not_template_t<T>::value;






static_assert(std::is_same_v< int, TyTuple<int, int>::get<0> >, "");
static_assert(std::is_same_v< unwrap<X<int, float>>::get<1>, float >, "");

static_assert(std::is_same_v< repack<X<int, float>, int, float>, X<int, float> >, "");


static_assert(std::is_same_v< repack<X<int, float>, int, float>, unwrap<X<int, float>>::rewrap<X> >, "");


template <typename T, typename U>
inline constexpr bool is_similar = std::is_same<std::remove_const_t<std::remove_reference_t<T>>, U>::value;


static_assert(is_similar<const int&, int>, "");
static_assert(!is_similar<const float&, int>, "");



































template <class T, template <class, class...> class U>
using is_instance_t = typename std::is_same<T, rewrap<T, U> >;





template <class T, template <class, class...> class U>
inline constexpr bool is_instance = is_similar<T, rewrap<T, U> >;





template <int N, class T, template <class, class...> class U>
inline constexpr bool is_instance_n = []() {
	if constexpr (unwrap<T>::size == N) {
		return is_similar<T, rewrap_cut<N, T, U> >;
	}
	return false;
}();








static_assert(!is_instance_n<2, X<int>, X>, "");
static_assert(is_instance_n<2, X<int, int>, X>, "");
static_assert(!is_instance_n<2, X<int, int, int>, X>, "");

static_assert(!is_instance<int, Number>, "");
static_assert(is_instance<Number<int>, Number>, "");
static_assert(is_instance<Number<X<int>>, Number>, "");


static_assert(is_instance<Number<int>, Number>, "");

static_assert(is_template_t<X<int, float>>::value, "");




















class VStar;


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

#line 9 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Show.h"












class IShow {
public:
	const auto show() const {
		return curry([this](const VStar& a) { return this->_show(a); });
	};
private:
	virtual FString _show(const VStar& a) const = 0;
};

































































#line 4 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"









include "Types/VStar.h"

#line 16 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Generated\\out_pre.h"









class IBool : public virtual ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const override {
		return &IBool::Instances;
	}
public:
	class Show : public virtual IShow {
	private:
		virtual FString _show(const VStar& me) const override;
	public:
		Show() = default;
	};
	inline static const Show ShowInst = {};

public:
	static const inline Typeclass Instances = []{ Typeclass ${}; $.Show = &IBool::ShowInst;; return $; }()

;
};





class Bool : public virtual IBool {
private:
	bool _value;

	friend IBool;
public:
	virtual ~Bool() = default;

	Bool(bool value) : _value(value) {};
	Bool(const Bool& other) : _value(other._value) {};


	virtual bool get() const { return _value; }

};

inline FString IBool::Show::_show(const VStar& me) const {
	
	bool a = me.ResolveToUnsafe<Bool>().get();

	
	
	return a ? FString(TEXT("O")) : FString(TEXT("X"));
}


