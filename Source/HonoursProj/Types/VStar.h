#pragma once

#include "CoreMinimal.h"

#include "Types/Type.h"
#include "Types/Unpack.h"

#ifndef PP__PREPROCESSING

#include <memory>
#include <type_traits>

#else

include <memory>
include <type_traits>

#endif

#include "Types/FDecl.h"



template <typename T, typename = int>
struct IsDataclass : std::false_type {};

template <typename T>
struct IsDataclass <T, decltype(( void )T::Instances, 0)> : std::true_type {};





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
	const Typeclass* storedInstances;
	//Instances insts;

public:
	// Default Constructor
	VStar() {
		storedType = NULL;
		storedValue.reset();
	}

	// Copy Constructor, Should be used sparingly
	VStar(const VStar& other) {
		storedType = other.storedType;
		storedValue = shared_void_ptr(other.storedValue);
	};

	// Move Constructor
	VStar(VStar&& other) {
		Replace(other);
	}

	// Equality op
	constexpr VStar& operator=(const VStar& other) {
		if (this == &other) return *this;

		storedType = other.storedType;
		//storedValue.reset();
		storedValue = other.storedValue;

		return *this;
	}

	VStar(UType* type) {
		// Release any held values
		storedValue.reset();
		// Todo, decide if this should be make const or deepcopy
		storedType = UTypeConst::MakeConst(type);
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
			storedInstances = &value.Instances;
		}
	}
	// Todo: Check UType against T
	template <typename T>
	VStar(T value) {
		// Copy the value onto the heap
		storedValue = shared_void(new T(value));
		// Todo, decide if this should be make const or deepcopy
		storedType = FromType<T>();
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
		// Destroy other
		other.storedValue.reset();
		other.storedType = NULL;
	}

	// Query the Type
	const UType* const Type() const {
		return storedType;
	}

	const Typeclass* const getTypeclass() const {
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
	typename std::enable_if_t< std::is_same_v<T, int> , bool>
	ValidCast(const UType* type) const {
		return type->GetType() == EType::INT;
	}

	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, float>, bool>
	ValidCast(const UType* type) const {
		return type->GetType() == EType::FLOAT;
	}

	template <typename T>
	typename std::enable_if_t< std::is_same_v<T, Number<VStar>>, bool>
	ValidCast(const UType* type) const {
		return type->GetType() == EType::NUMBER;
	}

	template <typename T>
	typename std::enable_if_t<
		is_instance<T, Number>
		&& !std::is_same_v<T, Number<VStar>>
	, bool>
	ValidCast(const UType* type) const {
		using T_0 = extract<T, 0>;
		// handle not a number
		if (type->GetType() != EType::NUMBER) {
			return false;
		}
		// Handle is a Number<VStar>
		else if (type->GetTemplates()[0]->GetType() == EType::NONE) {
			return GetUnsafePtr<NumberV>()->_value.ValidCast<T_0>();
		}
		// Handle is a Number<T>
		else {
			return ValidCast<T_0>(type->GetTemplates()[0]);
		}
		// Unreachable
		return false;
	}


	template <typename T>
	T* ResolveTo() {

	}



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