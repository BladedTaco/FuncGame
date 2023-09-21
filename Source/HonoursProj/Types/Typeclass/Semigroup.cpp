#include "Semigroup.h"

#include "Types/Dataclass/BaseTypes.h"

const Arr<const VStar&, Arr<const VStar&, VStar > > ISemigroup::stimes() const {
    return curry([this](const VStar& times, const VStar& group)->VStar { return this->_stimes(times, group); });
}; 
VStar ISemigroup::_stimes(const VStar& times, const VStar& group) const {
	VStar value = group;
	int t = times.ResolveToUnsafe<Int>().get();
	for (int i = t; i --> 2;) {
		value = mappend()(value)(group);
	}
	return value;
};

//// stimes :: Int -> a -> a
//TypeclassVirtualImpl(ISemigroup, VStar, stimes, times, group) {
//	VStar value = group;
//	int t = times.ResolveToUnsafe<Int>().get();
//	for (int i = t; i --> 2;) {
//		value = mappend()(value)(group);
//	}
//	return value;
//};