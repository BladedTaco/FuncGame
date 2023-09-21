#include "FDecl.h"


TSharedPtr<const Typeclass> ITypeclass::GetTypeclass() const {
	return _GetTypeclass(); 
};

TSharedPtr<const Typeclass> NoopPtr(const Typeclass* InTypeclass) {
	return TSharedPtr<const Typeclass>(InTypeclass, [](const Typeclass* _) {});
}