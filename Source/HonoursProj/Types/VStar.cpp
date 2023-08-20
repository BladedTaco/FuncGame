#include "VStar.h"

#include "Maybe_gen.h"
#include "Int_gen.h"
#include "Functional/curry_gen.h"

//// Number<...>
//template <typename T>
// typename std::enable_if_t<
//	is_instance_n<1, T, Number>
//	&& !std::is_same_v<T, NumberV>
//, bool>
//VStar::ValidCast(const UType* type) const {
//	using T_0 = extract<T, 0>;
//	// handle not a number
//	if (type->GetType() != EType::NUMBER) {
//		return false;
//	}
//	// Handle is a NumberV
//	else if (type->GetTemplates()[0]->GetType() == EType::NONE) {
//		return GetUnsafePtr<NumberV>()->_value.ValidCast<T_0>();
//	}
//	// Handle is a Number<T>
//	else {
//		return ValidCast<T_0>(type->GetTemplates()[0]);
//	}
//	// Unreachable
//	return false;
//}
//
//// Maybe<...>
//template <typename T>
// typename std::enable_if_t<
//	is_instance_n<1, T, Maybe>
//	&& !std::is_same_v<T, MaybeV>
//, bool>
//VStar::ValidCast(const UType* type) const {
//	using T_0 = extract<T, 0>;
//	// handle not a maybe
//	if (type->GetType() != EType::MAYBE) {
//		return false;
//	}
//	// Handle is a MaybeV
//	else if (type->GetTemplates()[0]->GetType() == EType::NONE) {
//		// Nothing Maybes can cast to anything
//		if (GetUnsafePtr<MaybeV>()->_isNothing) {
//			return true;
//		}
//		// Just Maybes can only cast to their inner values
//		return GetUnsafePtr<MaybeV>()->_value.ValidCast<T_0>();
//	}
//	// Handle is a Maybe<T>
//	else {
//		return ValidCast<T_0>(type->GetTemplates()[0]);
//	}
//	// Unreachable
//	return false;
//}
//
//// Arr<...>
//template <typename T>
// typename std::enable_if_t<
//	is_instance_n<2, T, Arr>
//	&& !std::is_same_v<T, ArrV>
//, bool>
//VStar::ValidCast(const UType* type) const {
//	using From = extract<T, 0>;
//	using To = extract<T, 1>;
//
//	// handle not an arrow
//	if (type->GetType() != EType::FUNC) {
//		return false;
//	}
//		
//	UE_LOG(LogTemp, Error, TEXT("Arrow casting not yet supported"));
//
//	// Destructure Templates
//	auto templates = type->GetTemplates();
//	auto [from, to] = Destruct<2, TArray, UType*>(templates);
//
//	// Handle is a ArrV
//	if (from->GetType() == EType::NONE) {
//		UE_LOG(LogTemp, Error, TEXT("Arrow casting not yet supported"));
//		return false;
//		//return GetUnsafePtr<MaybeV>()->_value.ValidCast<T_0>();
//	}
//	// Handle is a Arr<...>
//	else {
//		return ValidCast<From>(from) && ValidCast<To>(to);
//	}
//	// Unreachable
//	return false;
//}