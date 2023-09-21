#pragma once


#include "Types/Typeclass/Functor.h"
#include "Types/Typeclass/Applicative.h"
#include "Types/Typeclass/Monad.h"

#include "Types/Typeclass/Semigroup.h"
#include "Types/Typeclass/Monoid.h"

FUNCTOR(Func);
APPLICATIVE(Func);
MONAD(Func);

// Dependant
SEMIGROUP(Func);
MONOID(Func);



//// A Func is an arrow ((->) From) To
//template <typename To, typename From>
//class Func {
//private:
//	Function<To, From> _func;
//	friend class Functor<Func<To, From>>;
//public:
//	Func(Function<To, From> f) {
//		_func = f;
//	}
//	To operator()(const From& a) const {
//		return _func(a);
//	}
// //};

// FUNCTOR((A, From), Func,
// 	([](Arr<A, B> func, Arr<From, A> f_a) -> Arr<From, B> {	PP__NEWLINE
// 	return { [=](const From& a) {							PP__NEWLINE
// 		return func(f_a(a)); 								PP__NEWLINE
// 	} };
// }),
// ()
// );
 