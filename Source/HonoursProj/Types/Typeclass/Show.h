#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"
//
//
//// Functor Instance Macro
#define SHOW(INST)		 \
PP__DIRECTIVE(Typeclass, Show, INST)

// Functor Interface
class IShow {
public:
	const auto show() const {
		return curry([this](const VStar& a) { return this->_show(a); });
	};
private:
	virtual FString _show(const VStar& a) const = 0;
};


