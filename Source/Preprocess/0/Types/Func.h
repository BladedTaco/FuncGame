#pragma once


#include "Types/Functor.h"

// A Func is an arrow ((->) From) To
template <typename To, typename From>
class Func {
private:
	Function<To, From> _func;
	friend class Functor<Func<To, From>>;
public:
	Func(Function<To, From> f) {
		_func = f;
	}
	To operator()(const From& a) const {
		return _func(a);
	}
};

// More readable template switch
template <typename From, typename To>
using Arr = Func<To, From>;

FUNCTOR((A, From), Func, 
	([](Function<B, A> func, Arr<From, A> f_a) -> Arr<From, B> {	PP__NEWLINE
		return Arr<From, B>([=](const From& a) {					PP__NEWLINE
			return func(f_a(a)); 									PP__NEWLINE
		});
	}),
	()
);