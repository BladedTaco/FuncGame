#include "Types/Int_gen.h"

ORD INumber::Ordinal::_ord(const VStar& me, const VStar& other) const {
	if (me.ValidCast<Number<int>>()) {
		int a = me.GetUnsafePtr<Number<int>>()->get();
		int b = other.TryGet<Number<int>>()->get();

		return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;

	} else if (me.ValidCast<Number<float>>()) {
		float a = me.GetUnsafePtr<Number<float>>()->get();
		float b = other.TryGet<Number<float>>()->get();


		return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;

	}
	return ORD::LT;
}

template <typename A>
Number<A>::Number(const NumberV* other) {
	_value = other->_value.ResolveTo<A>();
}