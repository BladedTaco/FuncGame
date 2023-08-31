﻿// ---------------------------------------------------------------------------------------
// This File (curry_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "MacroUtils.h"
#include "Preprocess\Include.h"
#include <functional>
#include "Types/VStar.h"
#include "Types\FDecl.h"
namespace detail {
	template <typename F>
	struct function_traits : public function_traits<decltype(&F::operator())> {};
	template <typename R, typename C, typename... Args>
	struct function_traits<R(C::*)(Args...) const> {
		using function_type = std::function<R(Args...)>;
	};
}
template <typename F>
using function_type_t = typename detail::function_traits<F>::function_type;
template <typename F>
function_type_t<F> to_function(F& lambda) {
	return static_cast< function_type_t<F> >(lambda);
}
template <typename Return, typename... Params>
using Function = std::function<Return(Params...)>;
template <typename F>
class Functor;
class IFunc : public virtual ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const override;
public:
	class Functor;
	static const Functor FunctorInst;
	class Show;
	static const Show ShowInst;
public:
	static const Typeclass Instances;
};
template <typename To, typename From>
class Func : public virtual IFunc {
private:
	Function<To, From> _func;
public:
	Func(Function<To, From> f) {
		_func = f;
	}
	To operator()(const VStar& a) const {
		return _func(a.ResolveToUnsafe<From>());
	}
	To operator()(From a) const {
		return _func(a);
	}
};
template <typename To>
class Func<To, VStar> : public virtual IFunc {
	using From = const VStar&;
private:
	Function<To, From> _func;
public:
	Func(Function<To, From> f) {
		_func = f;
	}
	To operator()(From a) const {
		return _func(a);
	}
};
template <typename To>
class Func<To, const VStar&> : public virtual IFunc {
	using From = const VStar&;
private:
	Function<To, From> _func;
public:
	Func(Function<To, From> f) {
		_func = f;
	}
	To operator()(From a) const {
		return _func(a);
	}
};
template <>
class Func<VStarArrayReturn, VStarArray> : public virtual IFunc {
	using From = VStarArray;
	using To = VStarArrayReturn;
private:
	Function<To, From> _func;
public:
	Func(Function<To, From> f) {
		_func = f;
	}
	To operator()(From a) const {
		return _func(std::move(a));
	}
	To operator()(TArray<VStar> a) const {
		return _func(std::move(a));
	}
};
template <typename First, typename To>
inline Arr<First, To> _curry(Function<To, First> f) {
	return Arr<First, To>(f);
}
template <typename T_0 , typename T_1, typename To> 
 inline Arr<T_0, Arr<T_1, To > > 
 _curry(Function<To , T_0 , T_1> f) { 
 return Arr<T_0, Arr<T_1, To > > ([=]( T_0 V_0 ) { 
 return _curry<T_1, To>( 
 [=](T_1 V_1) -> To { 
 return f(V_0 , V_1); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, To > > > 
 _curry(Function<To , T_0 , T_1 , T_2> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, To > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2, To>( 
 [=](T_1 V_1 , T_2 V_2) -> To { 
 return f(V_0 , V_1 , V_2); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, To > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, To > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3) -> To { 
 return f(V_0 , V_1 , V_2 , V_3); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, To > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, To > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, To > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, To > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, To > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, To > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, To > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, To > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, To > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, To > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, To > > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, To > > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8 , T_9 V_9) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8 , V_9); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, To > > > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, To > > > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8 , T_9 V_9 , T_10 V_10) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8 , V_9 , V_10); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, To > > > > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, To > > > > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8 , T_9 V_9 , T_10 V_10 , T_11 V_11) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8 , V_9 , V_10 , V_11); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, Arr<T_12, To > > > > > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, Arr<T_12, To > > > > > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8 , T_9 V_9 , T_10 V_10 , T_11 V_11 , T_12 V_12) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8 , V_9 , V_10 , V_11 , V_12); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, Arr<T_12, Arr<T_13, To > > > > > > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, Arr<T_12, Arr<T_13, To > > > > > > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8 , T_9 V_9 , T_10 V_10 , T_11 V_11 , T_12 V_12 , T_13 V_13) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8 , V_9 , V_10 , V_11 , V_12 , V_13); 
 } 
 ); 
 }); 
 } 
 
 template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14, typename To> 
 inline Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, Arr<T_12, Arr<T_13, Arr<T_14, To > > > > > > > > > > > > > > > 
 _curry(Function<To , T_0 , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14> f) { 
 return Arr<T_0, Arr<T_1, Arr<T_2, Arr<T_3, Arr<T_4, Arr<T_5, Arr<T_6, Arr<T_7, Arr<T_8, Arr<T_9, Arr<T_10, Arr<T_11, Arr<T_12, Arr<T_13, Arr<T_14, To > > > > > > > > > > > > > > > ([=]( T_0 V_0 ) { 
 return _curry<T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14, To>( 
 [=](T_1 V_1 , T_2 V_2 , T_3 V_3 , T_4 V_4 , T_5 V_5 , T_6 V_6 , T_7 V_7 , T_8 V_8 , T_9 V_9 , T_10 V_10 , T_11 V_11 , T_12 V_12 , T_13 V_13 , T_14 V_14) -> To { 
 return f(V_0 , V_1 , V_2 , V_3 , V_4 , V_5 , V_6 , V_7 , V_8 , V_9 , V_10 , V_11 , V_12 , V_13 , V_14); 
 } 
 ); 
 }); 
 } 
 
 ;
template <typename F>
inline auto curry(F const& f) {
	return _curry(to_function(f));
}
template <typename F>
inline auto fcurry(F const& f) {
	return _curry(f);
}
