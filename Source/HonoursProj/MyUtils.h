#pragma once

#ifndef PP__PREPROCESSING

#include "CoreMinimal.h"
#include <tuple>        // tuple...
#include <type_traits>  // integral_constant

template <int N, template <typename> typename Cls, typename Type>
struct Destruct {
public:
	Cls<Type>* _inst;
	Destruct(Cls<Type>& inst) {
		_inst = &inst;
	}
};


template <int N, template <typename> typename Cls, typename Type>
struct DestructPtr {
public:
	Cls<Type>* _inst;
	DestructPtr(Cls<Type>& inst) {
		_inst = &inst;
	}
};

template <int N, typename... Types>
struct DestructTs : std::tuple<Types...> {};


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



	// Destruct
	template <int N, template <typename> typename Cls, typename Type>
	struct tuple_size<Destruct<N, Cls, Type>> : integral_constant<size_t, N> {};

	template <size_t Idx, int N, template <typename> typename Cls, typename Type>
	struct tuple_element<Idx, Destruct<N, Cls, Type>> { using type = Type; };

	template <size_t Idx, int N, template <typename> typename Cls, typename Type>
	Type& get(const Destruct<N, Cls, Type>& t) {
		return (*t._inst)[Idx];
	}


	// Destruct Ptr
	template <int N, template <typename> typename Cls, typename Type>
	struct tuple_size<DestructPtr<N, Cls, Type>> : integral_constant<size_t, N> {};

	template <size_t Idx, int N, template <typename> typename Cls, typename Type>
	struct tuple_element<Idx, DestructPtr<N, Cls, Type>> { using type = Type*; };

	template <size_t Idx, int N, template <typename> typename Cls, typename Type>
	Type* get(const DestructPtr<N, Cls, Type>& t) {
		return &(*t._inst)[Idx];
	}


	// Destruct Types
	template <int N, typename... Types>
	struct tuple_size<DestructTs<N, Types...>> : integral_constant<size_t, N> {};

	template <size_t Idx, int N, typename... Types>
	struct tuple_element<Idx, DestructTs<N, Types...>> : std::tuple_element<Idx, std::tuple<Types...>> {};

	template <size_t Idx, int N, typename... Types>
	auto get(const DestructTs<N, Types...>& t) -> tuple_element_t < Idx, decltype(t) >* {
		return (tuple_element_t < Idx, decltype(t) >*) & NULL;
	}

};

#endif

FVector MousePosWorld(UWorld* WorldContext);
FVector MousePosScreen(UWorld* WorldContext);


void FitActorToPlane(AActor* Actor, UStaticMeshComponent* Plane);
void FitActorToPlane(AActor* Actor, FVector ActorOrigin, FVector ActorRange, UStaticMeshComponent* Plane);
void FitActorToPlane(AActor* Actor, class UBoxComponent* ActorBounds, UStaticMeshComponent* Plane);