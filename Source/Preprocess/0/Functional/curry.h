#pragma once

#include "MacroUtils.h"
#include "Preprocess/Include.h"

#ifndef PP__PREPROCESSING
#include <functional>
#include "Types/VStar.h"
#else
include <functional>
include "Types/VStar.h"
#endif

#include "Types/FDecl.h"

// Lambda to Function Casting

//https://gist.github.com/khvorov/cd626ea3685fd5e8bf14
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



// Function Shorthand
template <typename Return, typename... Params>
using Function = std::function<Return(Params...)>;

template <typename F>
class Functor;




class IFunc : public virtual ITypeclass {
private:
	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override;
public:
	class Functor;
	static const Functor FunctorInst;
	class Applicative;
	static const Applicative ApplicativeInst;
	class Monad;
	static const Monad MonadInst;

	class Semigroup;
	static const Semigroup SemigroupInst;
	class Monoid;
	static const Monoid MonoidInst;

	class Show;
	static const Show ShowInst;

public:
	static const Typeclass Instances;
};






// A Func is an arrow ((->) From) To
template <typename To, typename From>
class Func : public virtual IFunc {
private:
	Function<To, From> _func;
	//friend class Functor<Func<To, From>>;
public:
	// Copyable Lambdas
	Func(Function<To, From> f) {
		_func = f;
	}
	//// Copyable Lambdas
	//Func(Func<To, From>& other) {
	//	_func = other._func;
	//}
	//To operator()(VStarArray a) const {
	//	return _func(std::move(a));
	//}
	To operator()(const VStar& a) const {
		return _func(a.ResolveToUnsafe<From>());
	}
	//To operator()(const From& a) const {
	//	return _func(a);
	//}
	To operator()(From a) const {
		return _func(a);
	}
};

template <typename To>
class Func<To, VStar> : public virtual IFunc {
	using From = const VStar&;
private:
	Function<To, From> _func;
	//friend class Functor<Func<To, From>>;
public:
	// Copyable Lambdas
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
	//friend class Functor<Func<To, From>>;
public:
	// Copyable Lambdas
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
	//friend class Functor<Func<To, From>>;
public:
	// Copyable Lambdas
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

//// A Func is an arrow ((->) From) To
//template <typename To>
//class Func<To, VStarArray> {
//private:
//	Function<To, VStarArray> _func;
//	friend class Functor<Func<To, VStarArray>>;
//public:
//	Func(Function<To, VStarArray> f) {
//		_func = f;
//	}
//	To operator()(VStarArray a) const {
//		return _func(std::move(a));
//	}
//};




// Define Currying
#define DEFN_CURRY_T_(N) , T_##N
#define DEFN_CURRY_V_(N) , V_##N
#define DEFN_CURRY_TEMPS(N) , typename T_##N
#define DEFN_CURRY_RETURN(N) Arr<T_##N,
#define CLOSE_TEMPLATE(N) > 
#define DEFN_CURRY_PARAM(N) , T_## N V_## N

#define DEFINE_CURRY_N(...) \
template <MAP_BLIST(DEFN_CURRY_TEMPS, __VA_ARGS__), typename To>					PP__NEWLINE \
inline LOOP(DEFN_CURRY_RETURN, __VA_ARGS__) To LOOP(CLOSE_TEMPLATE, __VA_ARGS__)	PP__NEWLINE \
_curry(Function<To LOOP(DEFN_CURRY_T_, __VA_ARGS__)> f) {							PP__NEWLINE \
	return LOOP(DEFN_CURRY_RETURN, __VA_ARGS__) To LOOP(CLOSE_TEMPLATE, __VA_ARGS__)			\
		([=]( STRIP_FIRST(DEFN_CURRY_PARAM(0)) ) {									PP__NEWLINE \
		return _curry<MAP_BLIST(DEFN_CURRY_T_, IGNORE_FIRST(__VA_ARGS__)), To>(		PP__NEWLINE \
			[=](MAP_BLIST(DEFN_CURRY_PARAM, IGNORE_FIRST(__VA_ARGS__))) -> To {		PP__NEWLINE \
				return f(MAP_BLIST(DEFN_CURRY_V_, __VA_ARGS__));					PP__NEWLINE \
			}																		PP__NEWLINE \
		);																			PP__NEWLINE \
	});																				PP__NEWLINE \
}																		PP__NEWLINE PP__NEWLINE

#define DEFINE_CURRY(N) DEFINE_CURRY_N(TAKE_N(N, __NATURAL_64_INTS_ASC()))

#define DEFINE_CURRYS(N) LOOP2(DEFINE_CURRY, STRIP_FIRST(STRIP_FIRST(TAKE_N(N, __NATURAL_64_INTS_ASC()))))

// Curry Base Recursion
template <typename First, typename To>
inline Arr<First, To> _curry(Function<To, First> f) {
	return Arr<First, To>(f);
}

DEFINE_CURRYS(16);


// Curry a Lambda
template <typename F>
inline auto curry(F const& f) {
	return _curry(to_function(f));
}


// Curry a Function
template <typename F>
inline auto fcurry(F const& f) {
	return _curry(f);
}

//
//// Curry a Function
//template <typename Cls, typename To, typename... From>
//inline auto lcurry(To(Cls::*)(From...)& f) {
//	return curry([](From... args) {return f(args...); });
//}
//

//// Curry a Function
//template <typename F>
//inline auto lcurry(F const& f) {
//	return curry([&](auto&& ...args) {return f(args...); });
//}

//
//#define curry(...) _curry(to_function(PP__VA_ARGS__)))
//PP__DIRECTIVE(Define, curry, _curry(to_function(PP__VA_ARGS__)))
