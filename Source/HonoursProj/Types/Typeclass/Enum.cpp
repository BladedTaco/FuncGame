#include "Enum.h"

#include "Types/Dataclass/BaseTypes.h"

// toEnum :: Int -> a
const Arr<const VStar&, VStar > IEnum::toEnum() const {
	return curry([this](const VStar& integer)->VStar { return this->_toEnum(integer); });
};
// fromEnum :: a -> Int
const Arr<const VStar&, Int > IEnum::fromEnum() const {
    return curry([this](const VStar& value)->Int { return this->_fromEnum(value); });
};

// succ :: a -> a
const Arr<const VStar&, VStar > IEnum::succ() const {
	return curry([this](const VStar& value)->VStar { return this->_succ(value); });
}; VStar IEnum::_succ(const VStar& value) const {
	return toEnum()(Int(fromEnum()(value).get() + 1));
}
// pred :: a -> a
const Arr<const VStar&, VStar > IEnum::pred() const {
	return curry([this](const VStar& value)->VStar { return this->_pred(value); });
}; VStar IEnum::_pred(const VStar& value) const {
	return toEnum()(Int(fromEnum()(value).get() - 1));
}


//// toEnum :: Int -> a
//TypeclassVirtualImplPure(IEnum, VStar, toEnum, integer);
//// fromEnum :: a -> Int
//TypeclassVirtualImplPure(IEnum, Int, fromEnum, value);
//
//// succ :: a -> a
//TypeclassVirtualImpl(IEnum, VStar, succ, value) {
//	return toEnum()(fromEnum()(value).get() + 1);
//}
//// pred :: a -> a
//TypeclassVirtualImpl(IEnum, VStar, pred, value) {
//	return toEnum()(fromEnum()(value).get() - 1);
//}
