#pragma once

#include "CoreMinimal.h"

#include "Templates/UniquePtr.h"
#include "Types/Type.h"

#include <memory>
#include <type_traits>

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
			return ( T* )storedValue.get();
		}
		return ( T* )NULL;
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