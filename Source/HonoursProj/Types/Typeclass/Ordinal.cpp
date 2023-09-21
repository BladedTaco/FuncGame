#include "Ordinal.h"

#include "Types/Dataclass/BaseTypes.h"


// Ordinal Interface
const Arr<const VStar&, Arr<const VStar&, ORD > > IOrdinal::ord() const {
    return curry([this](const VStar& a, const VStar& b)->ORD { return this->_ord(a, b); });
};
const Arr<const VStar&, Arr<const VStar&, Bool > > IOrdinal::lt() const {
    return curry([this](const VStar& a, const VStar& b)->Bool { return this->_lt(a, b); });
}; Bool IOrdinal::_lt(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::LT; };
const Arr<const VStar&, Arr<const VStar&, Bool > > IOrdinal::lte() const {
    return curry([this](const VStar& a, const VStar& b)->Bool { return this->_lte(a, b); });
}; Bool IOrdinal::_lte(const VStar& a, const VStar& b) const { return _ord(a, b) != ORD::GT; };
const Arr<const VStar&, Arr<const VStar&, Bool > > IOrdinal::gt() const {
    return curry([this](const VStar& a, const VStar& b)->Bool { return this->_gt(a, b); });
}; Bool IOrdinal::_gt(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::GT; };
const Arr<const VStar&, Arr<const VStar&, Bool > > IOrdinal::gte() const {
    return curry([this](const VStar& a, const VStar& b)->Bool { return this->_gte(a, b); });
}; Bool IOrdinal::_gte(const VStar& a, const VStar& b) const { return _ord(a, b) != ORD::LT; };
const Arr<const VStar&, Arr<const VStar&, VStar > > IOrdinal::min() const {
    return curry([this](const VStar& a, const VStar& b)->VStar { return this->_min(a, b); });
}; VStar IOrdinal::_min(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::LT ? a : b; };
const Arr<const VStar&, Arr<const VStar&, VStar > > IOrdinal::max() const {
    return curry([this](const VStar& a, const VStar& b)->VStar { return this->_max(a, b); });
}; VStar IOrdinal::_max(const VStar& a, const VStar& b) const { return _ord(a, b) == ORD::GT ? a : b; };

 Bool IOrdinal::_eq(const VStar& a, const VStar& b) const { return Bool(_ord(a, b) == ORD::EQ); };
 Bool IOrdinal::_neq(const VStar& a, const VStar& b) const { return Bool(_ord(a, b) != ORD::EQ); };

//
//// Ordinal Interface
//TypeclassVirtualImplPure(IOrdinal, ORD, ord, a, b);
//TypeclassVirtualImpl(IOrdinal, Bool, lt, a, b) { return _ord(a, b) == ORD::LT; };
//TypeclassVirtualImpl(IOrdinal, Bool, lte, a, b) { return _ord(a, b) != ORD::GT; };
//TypeclassVirtualImpl(IOrdinal, Bool, gt, a, b) { return _ord(a, b) == ORD::GT; };
//TypeclassVirtualImpl(IOrdinal, Bool, gte, a, b) { return _ord(a, b) != ORD::LT; };
//TypeclassVirtualImpl(IOrdinal, VStar, min, a, b) { return _ord(a, b) == ORD::LT ? a : b; };
//TypeclassVirtualImpl(IOrdinal, VStar, max, a, b) { return _ord(a, b) == ORD::GT ? a : b; };
// 
// Bool IOrdinal::_eq(const VStar& a, const VStar& b) const { return Bool(_ord(a, b) == ORD::EQ); };
// Bool IOrdinal::_neq(const VStar& a, const VStar& b) const { return Bool(_ord(a, b) != ORD::EQ); };