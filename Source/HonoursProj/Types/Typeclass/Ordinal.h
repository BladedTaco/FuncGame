#pragma once


// Functor Instance Macro
#define ORDINAL(INST)				\
PP__DIRECTIVE(Typeclass, Ordinal, INST)

#define IORDINAL() 															PP__NEWLINE \
class Ordinal : public virtual IOrdinal {									PP__NEWLINE \
private:																	PP__NEWLINE \
	virtual ORD _ord( const VStar& a, const VStar& b) const override;		PP__NEWLINE \
public:																		PP__NEWLINE \
	Ordinal() = default;													PP__NEWLINE \
}; 																			PP__NEWLINE \
inline static const Ordinal OrdinalInst = {};

#include "Ordinal_gen.h"