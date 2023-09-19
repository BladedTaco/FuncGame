#include "Int_gen.h"


//
//template <typename A>
//ORD INumber<A>::Ordinal::_ord(const VStar& me, const VStar& other) const {
//	// Resolve
//	A a = me.ResolveToUnsafe<Number<A>>().get();
//	A b = other.ResolveToUnsafe<Number<A>>().get();
//
//	// Calculate
//	return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;
//
//	//if (me.ValidCast<Number<int>>()) {
//	//	int a = me.ResolveToUnsafe<Number<int>>().get();
//	//	int b = other.ResolveToUnsafe<Number<int>>().get();
//
//	//	return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;
//
//	//} else if (me.ValidCast<Number<float>>()) {
//	//	float a = me.ResolveToUnsafe<Number<float>>().get();
//	//	float b = other.ResolveToUnsafe<Number<float>>().get();
//
//
//	//	return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;
//
//	//}
//	//return ORD::LT;
//}
//



//template <typename A>
//Number<A>::Number(const NumberV* other) {
//	_value = other->_value.ResolveToUnsafe<A>();
//}