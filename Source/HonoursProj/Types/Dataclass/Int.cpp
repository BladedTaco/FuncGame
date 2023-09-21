#include "Int_gen.h"



FString IInt::Show::_show(const VStar& me) const {
	// Resolve
	int a = me.ResolveToUnsafe<Int>().get();

	return FString::Format(TEXT("{0}"), { a });
}

ORD IInt::Ordinal::_ord( const VStar& a, const VStar& b) const {
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();

	return _a == _b ? ORD::EQ : _a < _b ? ORD::LT : ORD::GT;
}


VStar IInt::Enum::_toEnum(const VStar& integer) const {
	return integer;
}	

Int IInt::Enum::_fromEnum(const VStar& value) const {
	return value.ResolveToUnsafe<Int>();
}

VStar IInt::Bounded::_minBound() const { return Int(INT_MIN); }
VStar IInt::Bounded::_maxBound() const { return Int(INT_MAX); }

VStar IInt::Num::_plus  ( const VStar& a , const VStar& b ) const 	{
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();
	return Int(_a + _b);
}

VStar IInt::Num::_minus ( const VStar& a , const VStar& b ) const	{
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();
	return Int(_a - _b);
}

VStar IInt::Num::_times ( const VStar& a , const VStar& b ) const	{
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();
	return Int(_a * _b);
}

VStar IInt::Num::_abs   ( const VStar& value ) const				{
	int _a = value.ResolveToUnsafe<Int>().get();
	return Int(_a * _sign(value).ResolveToUnsafe<Int>().get());
}

VStar IInt::Num::_sign  ( const VStar& value ) const				{
	int _a = value.ResolveToUnsafe<Int>().get();
	return Int((_a > 0) - (_a < 0));
}

VStar IInt::Num::_fromInt ( const VStar& integer ) const		{
	return integer;
}










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