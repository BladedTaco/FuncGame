#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

#include "Types/Dataclass/BaseTypes.h"

// (+) :: a -> a -> a
const Arr<const VStar&, Arr<const VStar&, VStar > > INum::plus() const {
	return curry([this](const VStar& a, const VStar& b)->VStar { return this->_plus(a, b); });
};
// (-) :: a -> a -> a
const Arr<const VStar&, Arr<const VStar&, VStar > > INum::minus() const {
	return curry([this](const VStar& a, const VStar& b)->VStar { return this->_minus(a, b); });
};
// (*) :: a -> a -> a
const Arr<const VStar&, Arr<const VStar&, VStar > > INum::times() const {
	return curry([this](const VStar& a, const VStar& b)->VStar { return this->_times(a, b); });
};
// abs :: a -> a
const Arr<const VStar&, VStar > INum::abs() const {
	return curry([this](const VStar& value)->VStar { return this->_abs(value); });
};
// signum :: a -> a
const Arr<const VStar&, VStar > INum::sign() const {
	return curry([this](const VStar& value)->VStar { return this->_sign(value); });
};
// fromInteger :: Int -> a
const Arr<const VStar&, VStar > INum::fromInt() const {
	return curry([this](const VStar& integer)->VStar { return this->_fromInt(integer); });
};

// negate :: a -> a
const Arr<const VStar&, VStar > INum::negate() const {
	return curry([this](const VStar& value)->VStar { return this->_negate(value); });
}; VStar INum::_negate(const VStar& value) const {
	VStar zero = fromInt()(Int(0));
	return minus()(zero)(value);
}

//
//// (+) :: a -> a -> a
//TypeclassVirtualImplPure(INum, VStar, plus, a, b);
//// (-) :: a -> a -> a
//TypeclassVirtualImplPure(INum, VStar, minus, a, b);
//// (*) :: a -> a -> a
//TypeclassVirtualImplPure(INum, VStar, times, a, b);
//// abs :: a -> a
//TypeclassVirtualImplPure(INum, VStar, abs, value);
//// signum :: a -> a
//TypeclassVirtualImplPure(INum, VStar, sign, value);
//// fromInteger :: Int -> a
//TypeclassVirtualImplPure(INum, VStar, fromInt, integer);
//
//// negate :: a -> a
//TypeclassVirtualImpl(INum, VStar, negate, value) {
//	VStar zero = fromInt()(Int(0));
//	return minus()(zero)(value);
//}