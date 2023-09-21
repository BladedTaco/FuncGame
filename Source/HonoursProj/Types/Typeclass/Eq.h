#pragma once

//// Functor Instance Macro
#define EQ(INST)		 \
PP__DIRECTIVE(Typeclass, Eq, INST)


#define IEQ() 																PP__NEWLINE \
class Eq : public virtual IEq {												PP__NEWLINE \
private:																	PP__NEWLINE \
	virtual Bool _eq(const VStar& a, const VStar& b) const override;		PP__NEWLINE \
public:																		PP__NEWLINE \
	Eq() = default;															PP__NEWLINE \
}; 																			PP__NEWLINE \
inline static const Eq EqInst = {};

#include "Eq_gen.h"