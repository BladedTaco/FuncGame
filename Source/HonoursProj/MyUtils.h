#pragma once

#ifndef PP__PREPROCESSING

#include "CoreMinimal.h"
#include <tuple>        // tuple...
#include <type_traits>  // integral_constant

namespace std {
	template <typename... Types> 
	struct tuple_size<TTuple<Types...>> : integral_constant<size_t, sizeof...(Types)> {};

	template <size_t Idx, typename... Types> 
	struct tuple_element<Idx, TTuple<Types...>> : tuple_element<Idx, tuple<Types...>> {};

	template <size_t Idx, typename... Types> 
	decltype(auto) get(const TTuple<Types...>& t) { 
		return(t.template Get<Idx>()); 
	}

	template <size_t Idx, typename... Types> 
	decltype(auto) get(const TTuple<Types...>&& t) { 
		return(t.template Get<Idx>()); 
	}

	template <size_t Idx, typename... Types> 
	decltype(auto) get(TTuple<Types...>&& t) { 
		return(t.template Get<Idx>()); 
	}

};



#endif