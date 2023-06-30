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

FUNCTOR((A, From), Func, 
	([](Arr<A, B> func, Arr<From, A> f_a) -> Arr<From, B> {	PP__NEWLINE
		return Arr<From, B>([=](const From& a) {					PP__NEWLINE
			return func(f_a(a)); 									PP__NEWLINE
		});
	}),
	()
);