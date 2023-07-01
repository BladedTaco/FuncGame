#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "CoreMinimal.h"

// Functor Instance Macro
#define FUNCTOR(TEMPLATES, INST, FMAP, MAP_REPLACE_BY)		 \
PP__DIRECTIVE(Typeclass, Functor, INST)						 \
TEMPLATE(UNBRACKET TEMPLATES)								 \
TYPECLASS_DEFN(Functor, TEMPLATES, INST) {					 \
	TYPECLASS_FUNC((B), fmap, FMAP)							 \
	TYPECLASS_OPT_FUNC((B), map_replace_by, MAP_REPLACE_BY)	 \
};

// Functor Class Template
template <typename From, typename To>
class Arrow {
protected:
	// Required
	inline static Function<Arrow<From, To>, Function<To, From>> _arr;
	template <typename B>
	inline static Function<Arrow<TTuple<From, B>, TTuple<To, B>>, Arrow<From, To>> _first;
	// optional
	template <typename From_2, typename To_2>
	inline static Function<Arrow<TTuple<From, From_2>, TTuple<To, To_2>>, Arrow<From, To>, Arrow<From_2, To_2>> _bimap;
	template <typename To_2>
	inline static Function<Arrow<From, TTuple<To, To_2>>, Arrow<From, To>, Arrow<From, To_2>> _fanout;
	template <typename B>
	inline static Function<Arrow<TTuple<B, From>, TTuple<B, To>>, Arrow<From, To>> _second;

public:
	// Required
	inline static auto arr = curry(Arrow<From, To>::_arr);
	template <typename B>
	inline static auto first = curry(Arrow<From, To>::_first<B>);
	// optional
	template <typename From_2, typename To_2>
	inline static auto bimap = curry(Arrow<From, To>::_bimap<From_2, To_2>);
	template <typename To_2>
	inline static auto fanout = curry(Arrow<From, To>::_fanout<To_2>);
	template <typename B>
	inline static auto second = curry(Arrow<From, To>::_second<B>);

};

// Functor Base Instance
template <template <class, class, class...> class F, typename From, typename To, typename... Rest>
class BaseArrow {
protected:
	// Required
	inline static Function<Arrow<From, To>, Function<To, From>> _arr;
	template <typename B>
	inline static auto _first = [](Arrow<From, To> f) -> Arrow<TTuple<From, B>, TTuple<To, B>> {
		return Arrow<B, B>::bimap<From, To>(f)(Prelude::id<B>);
	}

	// optional
	template <typename From_2, typename To_2>
	inline static auto _bimap = [](Arrow<From, To> f, Arrow<From_2, To_2> g) -> Arrow<TTuple<From, From_2>, TTuple<To, To_2>> {
		// f *** g = first f >>> arr swap >>> first g >>> arr swap
		// where swap (x, y) = (y, x)
		
		/*auto swap_f_to_g = Arrow<From, From_2>::arr(Prelude::swap<From, From_2>);
		auto swap_g_to_f = Arrow<From_2, From>::arr(Prelude::swap<From_2, From>);
		auto first_f = Arrow<From, To>::first<From_2>(f);
		auto first_g = Arrow<From_2, To_2>::first<From>(g);
		auto x = [](From y) { return swap_g_to_f(first_g(swap_f_to_g(first_f(y)))) };*/
		//return x;

		return Arrow<TTuple<From, From_2>, TTuple<To, To_2>>::arr(
			[](TTuple<From, From_2> tup) -> TTuple<To, To_2> {
				return MakeTuple(
					f(tup.Get<0>()),
					g(tup.Get<1>()),
				);
			}
		);
	};
	template <typename To_2>
	inline static auto _fanout = [](Arrow<From, To> f, Arrow<From, To_2> g) -> Arrow<From, TTuple<To, To_2>> {
		// f &&& g = arr (\b -> (b,b)) >>> f *** g
		return Arrow<From, TTuple<To, To_2>>::arr([](From a) -> TTuple<To, To_2> {
			return MakeTuple(f(a), g(a));
		});
	};
	template <typename B>
	inline static auto _second = [](Arrow<From, To> f) -> Arrow<TTuple<B, From>, TTuple<B, To>> {
		// second = (id ***)
		return Arrow<B, B>::bimap<From, To>(Prelude::id<B>)(f);
	};
public:
	// Required
	inline static auto arr = curry(_arr);
	template <typename B>
	inline static auto first = curry(_first<B>);
	// optional
	template <typename From_2, typename To_2>
	inline static auto bimap = curry(_bimap<From_2, To_2>);
	template <typename To_2>
	inline static auto fanout = curry(_fanout<To_2>);
	template <typename B>
	inline static auto second = curry(_second<B>);
};


