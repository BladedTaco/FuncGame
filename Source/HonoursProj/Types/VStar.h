#pragma once

#include "CoreMinimal.h"

#include "Type.h"
#include "Unpack.h"

#ifndef PP__PREPROCESSING

#include <memory>
#include <type_traits>
#include "Templates/SharedPointer.h"

#else

include <memory>
include <type_traits>
include "Templates/SharedPointer.h"

#endif

#include "FDecl.h"
#include "MyUtils.h"

#include "Templates/EnableIf.h"

//
//template <typename T, typename = int>
//struct IsDataclass : std::false_type {};
//
//template <typename T>
//struct IsDataclass <T, decltype(( void )T::Instances, 0)> : std::true_type {};
//
//template <typename T>
//struct IsDataclass <T, decltype(( void )std::declval<T>().Instances, 0)> : std::true_type {};











template <typename T>
struct IsDataclass : std::is_base_of<ITypeclass, T> {};



class UniqueVStar {
// Helpers
private:
	// https://stackoverflow.com/questions/39288891/why-is-shared-ptrvoid-legal-while-unique-ptrvoid-is-ill-formed
	// https://stackoverflow.com/a/39288979/
	// std::unique_ptr for void*
	using unique_void_ptr = std::unique_ptr<void, void(*)(void const*)>;

	// Constructs a std::unique_ptr for void* from any value type
	template<typename T>
	static auto unique_void(T* ptr) -> unique_void_ptr {
		return unique_void_ptr(ptr, [](void const* data) {
			T const* p = static_cast< T const* >(data);
			//std::cout << "{" << *p << "} located at [" << p << "] is being deleted.\n";
			delete p;
		});
	}

	// Member Declarations
private:
	unique_void_ptr storedValue = unique_void(new int(0));
	UType* storedType;

public:
	// Default Constructor
	UniqueVStar() {
		storedType = NULL;
		storedValue.reset();
	}

	// Move Constructor
	UniqueVStar(UniqueVStar&& other) {
		Replace(other);
	}

	UniqueVStar(UType* type) {
		// Release any held values
		storedValue.reset();
		// Todo, decide if this should be make const or deepcopy
		storedType = UTypeConst::MakeConst(type);
	}
	// Todo: Check UType against T
	template <typename T>
	UniqueVStar(UType* type, T value) {
		// Copy the value onto the heap
		storedValue = unique_void(new T(value));
		// Todo, decide if this should be make const or deepcopy
		storedType = UTypeConst::MakeConst(type);
	}

	// Checks if both type and value are valid
	bool Valid() const {
		return storedType && storedValue;
	}

	// Steals from Other, Replacing it
	void Replace(UniqueVStar& other) {
		// Steal from other
		storedValue.swap(other.storedValue);
		storedType = other.storedType;
		// Destroy other
		other.storedValue.reset();
		other.storedType = NULL;
	}

	// Query the Type
	UType* Type() {
		return storedType;
	}

	template <typename T>
	bool ValidCast() {
		switch (storedType->GetType()) {
		case EType::INT:
			return std::is_same_v<int, T>;
		case EType::FLOAT:
			return std::is_same_v<float, T>;
		default:
			return false;
		}
	}

	template <typename T>
	T* TryGet() {
		if (ValidCast<T>()) {
			return (T*)storedValue.get();
		}
		return (T*)NULL;
	}

	// Unsafe, Unchecked, Get
	template <typename T>
	T GetUnsafe() {
		return *(( T* )storedValue.get());
	}

	// Runtime Checked Get
	template <typename T>
	T Get() {
		if (!ValidCast<T>()) {
			UE_LOG(LogTemp, Fatal, TEXT("Invalid Cast from %s to %s"), 
				*UEnum::GetValueAsString(storedType->GetType()), 
				typeid(T).name()
			);
		}
		return *(( T* )storedValue.get());
	}
};
//
//template <typename = void*>
//struct IFunctor {
//	Arr<VStar, Arr<VStar, VStar>>* fmap = NULL;
//	Arr<VStar, Arr<VStar, VStar>>* map_replace_by = NULL;
//
//	Arr<VStar, Arr<VStar, VStar>>(*bfmap)(VStar) = NULL;
//
//
//	template <class B>
//	Arr<VStar, Arr<VStar, B>>(*bffmap)(B) = NULL;
//
//	template <class B>
//	Function<Arr<VStar, Arr<VStar, B>>, B> bbfmap;
//};
//
//struct Instances {
//	IFunctor<> Functor;
//};




class VStar {
	// Member Declarations
private:
	using shared_void_ptr = std::shared_ptr<void>;
// Constructs a std::unique_ptr for void* from any value type
	template<typename T>
	static auto shared_void(T* ptr) -> shared_void_ptr {
		return shared_void_ptr(ptr, [](void const* data) {
			T const* p = static_cast< T const* >(data);
			//std::cout << "{" << *p << "} located at [" << p << "] is being deleted.\n";
			delete p;
		});
	}


private:
	shared_void_ptr storedValue;
	UType* storedType;
	TSharedPtr<const Typeclass> storedInstances;
	//Instances insts;

public:
	// Default Constructor
	VStar() {
		storedType = NULL;
		storedValue.reset();
	}

	template <typename T>
	static VStar New() {
		VStar inst = VStar();
		inst.storedValue.reset();
		inst.storedType = FromType<T>();
		return inst;
	}

	// Copy Constructor, Should be used sparingly
	VStar(const VStar& other) {
		storedType = other.storedType;
		storedValue = other.storedValue;
		storedInstances = other.storedInstances;
	};

	// Move Constructor
	VStar(VStar&& other) {
		Replace(other);
	}

	// Assignment op
	constexpr VStar& operator=(const VStar& other) {
		if (this == &other) return *this;

		storedType = other.storedType;
		//storedValue.reset();
		storedValue = other.storedValue;
		storedInstances = other.storedInstances;

		return *this;
	}


	// Todo: Check UType against T
	template <typename T>
	VStar(UType* type, T value) {
		// Copy the value onto the heap
		storedValue = shared_void(new T(value));
		// Todo, decide if this should be make const or deepcopy
		storedType = UTypeConst::MakeConst(type);
		// Get Instances Pointer
		if constexpr (IsDataclass<T>::value) {
			storedInstances = value.GetTypeclass();
		}
	}
	// Todo: Check UType against T
	template <typename T>
	VStar(T value) {
		// Copy the value onto the heap
		storedValue = shared_void(new T(value));
		// Todo, decide if this should be make const or deepcopy
		storedType = FromType<T>();
		// Get Instances Pointer
		if constexpr (IsDataclass<T>::value) {
			storedInstances = value.GetTypeclass();
		}
	}
	// Todo: Check UType against T
	template <typename T>
	VStar(Arr<VStar, T> value) {
		// Copy the value onto the heap
		storedValue = shared_void(new ArrV(value.ToArrV()));
		// Todo, decide if this should be make const or deepcopy
		storedType = FromType<ArrV>();
		// Get Instances Pointer
		if constexpr (IsDataclass<T>::value) {
			storedInstances = value.GetTypeclass();
		}
	}

	template <>
	VStar(UType* type) {
		// Release any held values
		storedValue.reset();
		// Todo, decide if this should be make const or deepcopy
		storedType = UTypeConst::MakeConst(type); 
	}


	// Checks if both type and value are valid
	bool Valid() const {
		return storedType && storedValue;
	}

	// Steals from Other, Replacing it
	void Replace(VStar& other) {
		// Steal from other
		storedValue.swap(other.storedValue);
		storedType = other.storedType;
		storedInstances = other.storedInstances;
		// Destroy other
		other.storedValue.reset();
		other.storedType = NULL;
		other.storedInstances = NULL;
	}

	// Query the Type
	const UType* const Type() const {
		return storedType;
	}

	TSharedPtr<const Typeclass> const getTypeclass() const {
		return storedInstances;
	}


	template <typename T>
	bool ValidCast() const {
		 return ValidCast<T>(storedType);
	}

	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, VStar>, bool>
	ValidCast(const UType* type) const {
		return true;
	}


	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, Int> , bool>
	ValidCast(const UType* type) const {
		return type->GetType() == EType::INT;
	}

	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, float>, bool>
	ValidCast(const UType* type) const {
		return type->GetType() == EType::FLOAT;
	}

	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, Bool>, bool>
		ValidCast(const UType* type) const {
		return type->GetType() == EType::BOOL;
	}

	//// NumberV
	//template <typename T>
	//typename std::enable_if_t< std::is_same_v<T, Num>, bool>
	//ValidCast(const UType* type) const {
	//	return type->GetType() == EType::NUM;
	//}

	//// Number<...>
	//template <typename T>
	//typename std::enable_if_t<
	//	is_instance_n<1, T, Number>
	//	&& !std::is_same_v<T, NumberV>
	//, bool>
	//ValidCast(const UType* type) const {
	//	using T_0 = extract<T, 0>;
	//	// handle not a number
	//	if (type->GetType() != EType::NUMBER) {
	//		return false;
	//	}
	//	// Handle is a NumberV
	//	else if (type->GetTemplates()[0]->GetType() == EType::NONE) {

	//		return true;
	//		//return GetUnsafePtr<NumberV>()->template _value.ValidCast<T_0>();
	//	}
	//	// Handle is a Number<T>
	//	else {
	//		return ValidCast<T_0>(type->GetTemplates()[0]);
	//	}
	//	// Unreachable
	//	return false;
	//}

	// MaybeV
	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, MaybeV>, bool>
		ValidCast(const UType* type) const {
		return type->GetType() == EType::MAYBE;
	}

	// Maybe<...>
	template <typename T>
	typename std::enable_if_t<
		is_instance_n<1, T, Maybe>
		&& !std::is_same_v<T, MaybeV>
	, bool>
	ValidCast(const UType* type) const {
		using T_0 = extract<T, 0>;
		// handle not a maybe
		if (type->GetType() != EType::MAYBE) {
			return false;
		}
		// Handle is a MaybeV
		else if (type->GetTemplates()[0]->GetType() == EType::NONE) {

			return true;
			//// Nothing Maybes can cast to anything
			//if (GetUnsafePtr<MaybeV>()->_isNothing) {
			//	return true;
			//}
			//// Just Maybes can only cast to their inner values
			//return GetUnsafePtr<MaybeV>()->_value.ValidCast<T_0>();

		}
		// Handle is a Maybe<T>
		else {
			return ValidCast<T_0>(type->GetTemplates()[0]);
		}
		// Unreachable
		return false;
	}

	// ArrV
	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, ArrV>, bool>
	ValidCast(const UType* type) const {
		return type->GetType() == EType::FUNC;
	}

	// Arr<...>
	template <typename T>
	typename std::enable_if_t<
		is_instance_n<2, T, Arr>
		&& !std::is_same_v<T, ArrV>
	, bool>
	ValidCast(const UType* type) const {
		using From = extract<T, 0>;
		using To = extract<T, 1>;

		// handle not an arrow
		if (type->GetType() != EType::FUNC) {
			return false;
		}
		
		UE_LOG(LogTemp, Error, TEXT("Arrow casting not yet supported"));

		// Destructure Templates
		auto templates = type->GetTemplates();
		auto [from, to] = Destruct<2, TArray, UType*>(templates);

		// Handle is a ArrV
		if (from->GetType() == EType::NONE) {
			UE_LOG(LogTemp, Error, TEXT("Arrow casting not yet supported"));
			return false;
			//return GetUnsafePtr<MaybeV>()->_value.ValidCast<T_0>();
		}
		// Handle is a Arr<...>
		else {
			return ValidCast<From>(from) && ValidCast<To>(to);
		}
		// Unreachable
		return false;
	}



	// ListV
	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, ListV>, bool>
		ValidCast(const UType* type) const {
		return type->GetType() == EType::LIST;
	}

	// List<...>
	template <typename T>
	typename std::enable_if_t<
		is_instance_n<1, T, List>
		&& !std::is_same_v<T, ListV>
	, bool>
		ValidCast(const UType* type) const {
		using T_0 = extract<T, 0>;
		// handle not a list
		if (type->GetType() != EType::LIST) {
			return false;
		}
		// Handle is a ListV
		else if (type->GetTemplates()[0]->GetType() == EType::NONE) {

			return true;
			//// Nothing Maybes can cast to anything
			//if (GetUnsafePtr<MaybeV>()->_isNothing) {
			//	return true;
			//}
			//// Just Maybes can only cast to their inner values
			//return GetUnsafePtr<MaybeV>()->_value.ValidCast<T_0>();

		}
		// Handle is a List<T>
		else {
			return ValidCast<T_0>(type->GetTemplates()[0]);
		}
		// Unreachable
		return false;
	}


	// EitherV
	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, EitherV>, bool>
		ValidCast(const UType* type) const {
		return type->GetType() == EType::EITHER;
	}

	// Either<...>
	template <typename T>
	typename std::enable_if_t<
		is_instance_n<2, T, Either>
		&& !std::is_same_v<T, EitherV>
	, bool>
		ValidCast(const UType* type) const {
		using Left = extract<T, 0>;
		using Right = extract<T, 1>;

		// handle not an arrow
		if (type->GetType() != EType::EITHER) {
			return false;
		}

		// Destructure Templates
		auto templates = type->GetTemplates();
		auto [l, r] = Destruct<2, TArray, UType*>(templates);

		// Handle is a EitherV
		if (l->GetType() == EType::NONE || r->GetType() == EType::NONE) {

			EitherV* e = GetUnsafePtr<EitherV>();

			if (e->isLeft().get()) {
				return ValidCast<Left>(l);
			} else {
				return ValidCast<Right>(r);
			}
			//return GetUnsafePtr<MaybeV>()->_value.ValidCast<T_0>();
		}
		// Handle is a Either<...>
		else {
			return ValidCast<Left>(l) && ValidCast<Right>(r);
		}
		// Unreachable
		return false;
	}



public:
	template <typename T>
	std::unique_ptr<T> ResolveToSafe() const {
		if (!ValidCast<T>()) {
			return std::unique_ptr<T>(nullptr);
		}
		return std::make_unique<T>(ResolveTo<T>());
	}
	template <typename T>
	T ResolveToUnsafe() const {
		return ResolveTo<T>();
	}


private:
	// Any Atomic
	template <typename T>
	typename std::enable_if_t<
		not_template_t<T>::value, 
		T
	>
	ResolveTo() const {
		// copy constructor of atomic
		return T(*GetUnsafePtr<T>());
	}

	// Any<VStar...>
	template <typename T>
	typename std::enable_if_t<
		contains_only<T, VStar>::value, 
		T
	>
	ResolveTo() const {
		// Return Copy of Any<VStar...>
		return *GetUnsafePtr<T>();
	}

	// Any<Not VStar>
	template <typename T>
	typename std::enable_if_t< 
		is_template_t<T>::value && !contains_only<T, VStar>::value, 
		T
	>
	ResolveTo() const {
		// Rely on VStar Resolver Constructor
		return T(GetUnsafePtr<repack_fill<T, VStar>>());
	}
public:

	template <typename T>
	T* TryGet() {
		if (ValidCast<T>()) {
			return ( T* )storedValue.get();
		}
		return ( T* )NULL;
	}


	template <typename T>
	const T* const TryGet() const {
		if (ValidCast<T>()) {
			return ( T* )storedValue.get();
		}
		return ( T* )NULL;
	}

	// Unsafe, Unchecked, Get
	template <typename T>
	const T* GetUnsafePtr() const {
		return ( T* )storedValue.get();
	}

	// Unsafe, Unchecked, Get
	template <typename T>
	T GetUnsafe() {
		return *(( T* )storedValue.get());
	}

	// Runtime Checked Get
	template <typename T>
	T Get() {
		if (!ValidCast<T>()) {
			UE_LOG(LogTemp, Fatal, TEXT("Invalid Cast from %s to %s"),
				*UEnum::GetValueAsString(storedType->GetType()),
				*FString(typeid(T).name())
			);
		}
		return *(( T* )storedValue.get());
	}
};





/* TODO
Give Arr/Func needed constructors for typeclassing

HonoursProjPawn.cpp comment out Functor stuff, replace with new system

Check all Maybe stuff

*/





using VStarArray = TArray<VStar>&&;
using VStarArrayReturn = TArray<VStar>;


//
//template <typename T>
//class TStar : private VStar {
//public:
//	TStar()
//
//	T Get = VStar::Get<T>;
//};
//
//
//TStar a(1);
//
//auto n = a.Get();