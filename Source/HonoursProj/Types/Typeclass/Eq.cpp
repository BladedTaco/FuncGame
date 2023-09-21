#include "Eq.h"

#include "Types/Dataclass/BaseTypes.h"

const Arr<const VStar&, Arr<const VStar&, Bool > > IEq::eq() const {
	return curry([this](const VStar& a, const VStar& b)->Bool { return this->_eq(a, b); });
};

const Arr<const VStar&, Arr<const VStar&, Bool > > IEq::neq() const {
	return curry([this](const VStar& a, const VStar& b)->Bool { return this->_neq(a, b); });
}; Bool IEq::_neq(const VStar& a, const VStar& b) const {
	return Bool(!eq()(a)(b).get()); 
}


//
//
//TypeclassVirtualImplPure(IEq, Bool, eq, a, b);
//
//TypeclassVirtualImpl(IEq, Bool, neq, a, b) {
//	return Bool(!eq()(a)(b).get());
//}
//
//
