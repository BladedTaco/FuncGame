#pragma once

//// Functor Instance Macro
#define NUM(INST)		 \
PP__DIRECTIVE(Typeclass, Num, INST)


#define INUM() 																PP__NEWLINE \
class Num : public virtual INum {											PP__NEWLINE \
private:																	PP__NEWLINE \
	virtual VStar _plus  ( const VStar& a , const VStar& b ) const override;PP__NEWLINE \
	virtual VStar _minus ( const VStar& a , const VStar& b ) const override;PP__NEWLINE \
	virtual VStar _times ( const VStar& a , const VStar& b ) const override;PP__NEWLINE \
	virtual VStar _abs   ( const VStar& value ) const override;	 			PP__NEWLINE \
	virtual VStar _sign  ( const VStar& value ) const override;				PP__NEWLINE \
	virtual VStar _fromInt ( const VStar& integer ) const override;			PP__NEWLINE \
public:																		PP__NEWLINE \
	Num() = default;														PP__NEWLINE \
}; 																			PP__NEWLINE \
inline static const Num NumInst = {};

#include "Num_gen.h"