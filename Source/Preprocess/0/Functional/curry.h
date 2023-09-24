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
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override;

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
	friend ArrV;
	friend ArrVV;
public:
	// Copyable Lambdas
	virtual ~Func() = default;
	Func(Function<To, From> f);
	Func(const Func<To, From>* f);
	Func(const ArrV* f);
	Func(const ArrV& f);
	ArrV ToArrV() const;
	To operator()(From a) const;
	// To operator()(const From &a) const;
	// To operator()(const VStar &a) const;
};

template <>
class Func<VStar, VStar> : public virtual IFunc {
	using _From = const VStar&;
	using _To = VStar;
private:
	Function<_To, _From> _func;
	friend ArrVV;
	//friend class Functor<Func<To, From>>;
public:
	virtual ~Func() = default;
	// Copyable Lambdas
	inline Func(Function<_To, _From> f) {
		_func = f;
	}
	inline Func(const Func<_To, _From>* f) {
		_func = [f](VStar x) -> VStar { return f->operator()(x); };
	}
	inline Func(const ArrV* f) {
		_func = [f](VStar x) -> VStar { return f->operator()(x); };
	}
	inline ArrV ToArrV() const {
		return ArrV(_func);
	}
	inline _To operator()(_From a) const {
		return _func(a);
	}
}; 

template <typename To>
class Func<To, VStar> : public virtual IFunc {
	// using From = const VStar&;
private:
	Function<To, const VStar&> _func;
	friend ArrV;
	friend ArrVV;
	//friend class Functor<Func<To, From>>;
public:
	virtual ~Func() = default;
	// Copyable Lambdas
	Func(Function<To, const VStar&> f);
	Func(const Func<To, const VStar&>* f);
	Func(const ArrV* f);
	Func(const ArrVV* f);
	ArrV ToArrV() const;
	To operator()(const VStar& a) const;
};


template <typename To>
class Func<To, void> : public virtual IFunc {
	using _From = void;
private:
	Function<To> _func;
	friend ArrV;
	friend ArrVV;
	//friend class Functor<Func<To, From>>;
public:
	virtual ~Func() = default;
	// Copyable Lambdas
	Func(Function<To> f);
	Func(const Func<To, _From>* f);
	Func(const ArrV* f);
	Func(const ArrV& f);
	ArrV ToArrV() const;
	To operator()() const;
};


template <typename To>
class Func<To, const VStar&> : public virtual IFunc {
	using _From = const VStar&;
private:
	Function<To, _From> _func;
	friend ArrV;
	friend ArrVV;
	//friend class Functor<Func<To, From>>;
public:
	virtual ~Func() = default;
	// Copyable Lambdas
	Func(Function<To, _From> f);
	Func(const Func<To, _From>* f);
	Func(const ArrV* f);
	Func(const ArrV& f);
	ArrV ToArrV() const;
	To operator()(_From a) const;
};

template <>
class Func<VStarArrayReturn, VStarArray> : public virtual IFunc {
	using _From = VStarArray;
	using _To = VStarArrayReturn;
private:
	Function<_To, _From> _func;
	friend ArrV;
	friend ArrVV;
	//friend class Functor<Func<To, From>>;
public:
	virtual ~Func() = default;
	// Copyable Lambdas
	Func(Function<_To, _From> f) {
		_func = f;
	}
	Func(const Func<_To, _From>* f) {
		_func = f->_func;
	}
	_To operator()(_From a) const {
		return _func(std::move(a));
	}
	_To operator()(TArray<VStar> a) const {
		return _func(std::move(a));
	}

};











// TO FROM

// A Func is an arrow ((->) From) To
template <typename To, typename From>
Func<To, From>::Func(Function<To, From> f) {
	_func = f;
}
template <typename To, typename From>
Func<To, From>::Func(const Func<To, From>* f) {
	_func = f->_func;
}
template <typename To, typename From>
Func<To, From>::Func(const ArrV* f) {
	_func = [f](From x) -> To { return To(f->operator()(x)); };
}
template <typename To, typename From>
Func<To, From>::Func(const ArrV& f) {
	_func = [f](From x) -> To { return To(f(x)); };
} 
	//// Copyable Lambdas
	//Func(Func<To, From>& other) {
	//	_func = other._func;
	//}
	//To operator()(VStarArray a) const {
	//	return _func(std::move(a));
	//}
template <typename To, typename From>
inline ArrV Func<To, From>::ToArrV() const {
	auto _f = _func;
	if constexpr (is_instance_n<2, To, Arr>) {
		return curry([_f](VStar x){ return VStar(_f(x).ToArrV()); });
	}

	return curry([_f](VStar x){ return VStar(_f(x)); });
}
template <typename To, typename From>
inline To Func<To, From>::operator()(From a) const {
	return _func(a);
}
// template <typename To, typename From>
// inline To Func<To, From>::operator()(const From& a) const {
// 	return _func(a);
// }
// template <typename To, typename From>
// inline To Func<To, From>::operator()(const VStar& a) const {
// 	return _func(a.ResolveToUnsafe<From>());
// }


// VSTAR VSTAR
// Func<VStar, VStar>::Func(Function<VStar, const VStar&> f) {
// 	_func = f;
// }
// // template <>
// Func<VStar, VStar>::Func(const Func<VStar, const VStar&>* f) {
// 	_func = [f](VStar x) -> VStar { return f->operator()(x); };
// }
// // template <>
// Func<VStar, VStar>::Func(const ArrV* f) {
// 	_func = [f](VStar x) -> VStar { return f->operator()(x).ResolveToUnsafe<VStar>(); };
// }
// // Func(const ArrVV* f) {
// // 	_func = [f](From x) -> VStar { return VStar(f->operator()(x)); };
// // }
// // template <>
// inline ArrV Func<VStar, VStar>::ToArrV() const {
// 	return ArrV(_func);
// }
// // template <>
// inline VStar Func<VStar, VStar>::operator()(const VStar& a) const {
// 	return _func(a);
// }



	
// TO VSTAR
// Copyable Lambdas
template <typename To>
Func<To, VStar>::Func(Function<To, const VStar&> f) {
	_func = f;
}
template <typename To>
Func<To, VStar>::Func(const Func<To, const VStar&>* f) {
	_func = f->_func;
}
template <typename To>
Func<To, VStar>::Func(const ArrV* f) {
	_func = [f](const VStar& x) -> To { return f->operator()(x).ResolveToUnsafe<To>(); };
}
template <typename To>
Func<To, VStar>::Func(const ArrVV* f) {
	_func = [f](const VStar& x) -> VStar { return VStar(f->operator()(x)); };
}
template <typename To>
inline ArrV Func<To, VStar>::ToArrV() const {
	if constexpr (is_instance_n<2, To, Arr>) {
		return curry([_f = _func](VStar x){ return VStar(_f(x).ToArrV()); });
	}

	return curry([_f = _func](VStar x){ return VStar(_f(x)); });
}
template <typename To>
inline To Func<To, VStar>::operator()(const VStar& a) const {
	return _func(a);
}


// TO VOID

// Copyable Lambdas
template <typename To>
Func<To, void>::Func(Function<To> f) {
	_func = f;
}
template <typename To>
Func<To, void>::Func(const Func<To, void>* f) {
	_func = f->_func;
}
template <typename To>
Func<To, void>::Func(const ArrV* f) {
	_func = [f]() -> To { return To(f->operator()(VStar())); };
}
template <typename To>
Func<To, void>::Func(const ArrV& f) {
	_func = [f]() -> To { return To(f(VStar())); };
}

template <typename To>
inline ArrV Func<To, void>::ToArrV() const {
	if constexpr (is_instance_n<2, To, Arr>) {
		return curry([_f = _func](VStar x){ return VStar(_f().ToArrV()); });
	}

	return curry([_f = _func](VStar x){ return VStar(_f()); });
}

template <typename To>
inline To Func<To, void>::operator()() const {
	return _func();
}



// TO CONST VSTAR &

// Copyable Lambdas
template <typename To>
Func<To, const VStar&>::Func(Function<To, const VStar&> f) {
	_func = f;
}
template <typename To>
Func<To, const VStar&>::Func(const Func<To, const VStar&>* f) {
	_func = f->_func;
}
template <typename To>
Func<To, const VStar&>::Func(const ArrV* f) {
	_func = [f](const VStar& x) -> To { return To(f->operator()(x)); };
}
template <typename To>
Func<To, const VStar&>::Func(const ArrV& f) {
	_func = [f](const VStar& x) -> To { return To(f(x)); };
}

template <typename To>
inline ArrV Func<To, const VStar&>::ToArrV() const {
	if constexpr (is_instance_n<2, To, Arr>) {
		return curry([_f = _func](VStar x){ return VStar(_f(x).ToArrV()); });
	}

	return curry([_f = _func](VStar x){ return VStar(_f(x)); });
}

template <typename To>
inline To Func<To, const VStar&>::operator()(const VStar& a) const {
	return _func(a);
}



// VSTARARRAYRETURN VSTARARRAY

// Copyable Lambdas
// // template <>
// Func<VStarArrayReturn, VStarArray>::Func(Function<VStarArrayReturn, VStarArray> f) {
// 	_func = f;
// }
// template <>
// Func<VStarArrayReturn, VStarArray>::Func(const Func<VStarArrayReturn, VStarArray>* f) {
// 	_func = f->_func;
// }
// inline VStarArrayReturn Func<VStarArrayReturn, VStarArray>::operator()(VStarArray a) const {
// 	return _func(std::move(a));
// }
// inline VStarArrayReturn Func<VStarArrayReturn, VStarArray>::operator()(TArray<VStar> a) const {
// 	return _func(std::move(a));
// }
















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

// Curry 0
template <typename To>
inline Arr<void, To> _curry(Function<To> f) {
	return Arr<void, To>(f);
}

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
