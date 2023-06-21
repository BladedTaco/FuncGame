#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Functor.h"
#pragma once

#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"


#pragma once
#line 1 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\HonoursProj\\LoopMacros.h"


#pragma once




































































#line 5 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\MacroUtils.h"






















































































































#line 4 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Functor.h"





#line 10 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Functor.h"




include <functional>
#line 16 "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj\\Source\\Preprocess\\Types\\Functor.h"


template <typename Return, typename... Params>
using Function = std::function<Return(Params...)>;


template< class, class = std::void_t<> > struct
needs_unapply : std::true_type {};

template< class T > struct
needs_unapply<T, std::void_t<decltype(std::declval<T>()())>> : std::false_type {};


template <typename F> 
auto curry(F&& f) {
  
  
    if constexpr (needs_unapply<decltype(f)>::value) {
        return [=](auto&& x) {
            return curry(
                [=](auto&&...xs) -> decltype(f(x, xs...)) {
                return f(x, xs...);
            }
            );
        };
    } else {
      
        return f();
    }
}




namespace Prelude {
	
	template <typename A, typename B>
	auto constant = curry([](A a, B b) -> A {
		return a;
	});

	
	template <typename A, typename B, typename C>
	auto compose = curry([](Function<C, B> f, Function<B, A> g, A x) -> C {
		return f(g(x));
	});
	
	
	
	
	
};



template <typename A>
class Functor {
protected:
	template <typename B>
	inline static Function<Functor<B>, Function<B, A>, Functor<A>> _fmap;
	template <typename B>
	inline static Function<Functor<B>, Function<B, A>, Functor<A>> _map_replace_by;

public:
	template <typename B>
	inline static auto fmap = curry(Functor<A>::_fmap<B>);

	template <typename B>
	inline static auto map_replace_by = curry(Functor<A>::_map_replace_by<B>);

};





































template <template <class> class F, typename A>
class BaseFunctor {
protected:
	template <class B>
	inline static Function<F<B>, Function<B, A>, F<A>> _fmap;
	
	template <class B>
	inline static auto _map_replace_by = [](A a, F<B> f_b) -> F<A> {
		Function<A, B> f = Prelude::constant<A, B>(a);
		return Functor<F<B>>::fmap<A>(f)(f_b);
	};
public:
	template <class B>
	
	inline static auto fmap = curry(_fmap<B>);
	template <class B>
	inline static auto map_replace_by = curry(_map_replace_by<B>);
};

auto a = Prelude::constant<int, float>(1);

template <typename A>
class Maybe {
private:
	bool _isNothing;
	A _value;
	Maybe() {
		_isNothing = true;
		_value = false;
	}
	Maybe(A a) {
		_isNothing = false;
		_value = a;
	}
	friend class Functor<Maybe<A>>;
public:
	static Maybe<A> Just(A a) {
		return Maybe<A>(a);
	}
	static Maybe<A> Nothing() {
		return Maybe<A>();
	}
public:
	A fromMaybe(A fallback) {
		if (_isNothing) {
			return fallback;
		} else {
			return _value;
		}
	}
};

template <typename A>
auto fromMaybe = curry([](A a, Maybe<A> m_a) -> A {
	return m_a.fromMaybe(a);
});


template <typename A> class Functor<Maybe <A> > : public BaseFunctor<Maybe, A> { private: template <typename B> inline static auto _fmap = [](Function<B, A> func, Maybe<A> f_a) -> Maybe<B> { if (f_a._isNothing) { return Maybe<B>::Nothing(); } else { return Maybe<B>::Just(func(f_a._value)); } }; public: template <typename B> inline static auto fmap = curry(_fmap <B>); };








;



























































