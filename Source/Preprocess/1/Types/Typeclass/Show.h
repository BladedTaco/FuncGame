#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"
//
//


// Functor Interface
class IShow {
	TypeclassVirtual(FString, show, a) = 0;

// public:
// 	const auto show() const {
// 		return curry([this](const VStar& a) { return this->_show(a); });
// 	};
// private:
// 	virtual FString _show(const VStar& a) const = 0;
};


