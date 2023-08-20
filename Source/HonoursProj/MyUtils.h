#pragma once

#ifndef PP__PREPROCESSING

#include "CoreMinimal.h"
#include <tuple>        // tuple...
#include <type_traits>  // integral_constant

template <int N, template <typename...> typename Cls, typename Type>
struct Destruct {
public:
	Cls<Type>* _inst;
	Destruct(Cls<Type>& inst) {
		_inst = &inst;
	}
};


template <int N, template <typename...> typename Cls, typename Type>
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

	// Destruct
	template <int N, template <typename...> typename Cls, typename Type>
	class tuple_size<Destruct<N, Cls, Type>> : public integral_constant<size_t, N> {};

	template <size_t Idx, int N, template <typename...> typename Cls, typename Type>
	class tuple_element<Idx, Destruct<N, Cls, Type>> { public: using type = Type; };



	// Destruct Ptr
	template <int N, template <typename...> typename Cls, typename Type>
	class tuple_size<DestructPtr<N, Cls, Type>> : public integral_constant<size_t, N> {};

	template <size_t Idx, int N, template <typename...> typename Cls, typename Type>
	class tuple_element<Idx, DestructPtr<N, Cls, Type>> { public: using type = Type*; };


	// Destruct Types
	template <int N, typename... Types>
	class tuple_size<DestructTs<N, Types...>> : public integral_constant<size_t, N> {};

	template <size_t Idx, int N, typename... Types>
	class tuple_element<Idx, DestructTs<N, Types...>> : public std::tuple_element<Idx, std::tuple<Types...>> {};

};



template <size_t Idx, int N, template <typename...> typename Cls, typename Type>
Type& get(const Destruct<N, Cls, Type>& t) {
	return (*t._inst)[Idx];
}

template <size_t Idx, int N, template <typename...> typename Cls, typename Type>
Type* get(const DestructPtr<N, Cls, Type>& t) {
	return &(*t._inst)[Idx];
}

template <size_t Idx, int N, typename... Types>
auto get(const DestructTs<N, Types...>& t) -> std::tuple_element_t < Idx, decltype(t) >* {
	return (std::tuple_element_t < Idx, decltype(t) >*) NULL;
}

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



#endif


FVector MousePosWorld(UWorld* WorldContext);
FVector MousePosScreen(UWorld* WorldContext);

class AActor;
class UStaticMeshComponent;
class UBoxComponent;

void FitActorToPlane(AActor* Actor, UStaticMeshComponent* Plane);
void FitActorToPlane(AActor* Actor, FVector ActorOrigin, FVector ActorRange, UStaticMeshComponent* Plane);
void FitActorToPlane(AActor* Actor, UBoxComponent* ActorBounds, UStaticMeshComponent* Plane);