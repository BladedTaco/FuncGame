#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"
//
//
//// Functor Instance Macro
#define SHOW(TEMPLATES, INST, TO_STRING)		 \
PP__DIRECTIVE(Typeclass, Show, INST)						 
//TEMPLATE(UNBRACKET TEMPLATES)								 \
//TYPECLASS_DEFN(Show, TEMPLATES, INST) {					 \
//	TYPECLASS_FUNC((B), show, TO_STRING)							 \
//};


// Functor Interface
class IShow {
public:
	const auto show() const {
		return curry([this](const VStar& a) { return this->_show(a); });
	};
private:
	virtual FString _show(const VStar& a) const = 0;
};






//
//// Functor Class Template
//template <typename A>
//class Show {
//public:
//
//	inline static bool Valid = false;
//	static_assert(sizeof(A) == 0, "Only specializations of Functor can be used");
//
//	template <typename B>
//	inline static Function<Functor<B>, Arr<A, B>, Functor<A>> _fmap;
//	template <typename B>
//	inline static Function<Functor<B>, Arr<A, B>, Functor<A>> _map_replace_by;
//
//public:
//	template <typename B>
//	inline static auto fmap = curry(Functor<A>::_fmap<B>);
//
//	template <typename B>
//	inline static auto map_replace_by = curry(Functor<A>::_map_replace_by<B>);
//
//
//
//};
//
//
//// Functor Base Instance
//template <template <class, class...> class F, typename A, typename... Rest>
//class BaseFunctor {
//protected:
//	template <class B>
//	inline static Function<F<B, Rest...>, Arr<A, B>, F<A, Rest...>> _fmap;
//
//	template <class B>
//	inline static auto _map_replace_by = [](A a, F<B, Rest...> f_b) -> F<A, Rest...> {
//		Arr<B, A> f = { Prelude::constant<A, B>(a) };
//		return Functor<F<B, Rest...>>::fmap<A>(f)(f_b);
//	};
//public:
//	inline static bool Valid = true;
//	template <class B>
//	inline static auto fmap = curry(_fmap<B>);
//	template <class B>
//	inline static auto map_replace_by = curry(_map_replace_by<B>);
//
//	//TYPECLASS_FUNC_VPTR((B), fmap, ((Arr<A, B>), f), ((F<A, Rest...>), fa))
//	template <class B> inline static auto v_fmap = curry([](void* f, void* fa) -> decltype(auto) {
//		return fmap<B>(*(Arr<A, B>*)f) (*(F<A, Rest...>*)fa);
//	});
//
//	template <class B>
//	inline static auto vs_fmap = curry([](VStar f, VStar fa) -> VStar {
//		return VStar(
//			FromType<F<B, Rest...>>(),
//			fmap<B>(f.GetUnsafe<Arr<A, B>>())(fa.GetUnsafe<F<A, Rest...>>())
//		);
//	});
//};
//
