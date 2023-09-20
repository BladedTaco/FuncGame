#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

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

// Functor Interface
class INum {
	// (+) :: a -> a -> a
	TypeclassVirtual(VStar, plus, a, b) = 0;
	// (-) :: a -> a -> a
	TypeclassVirtual(VStar, minus, a, b) = 0;
	// (*) :: a -> a -> a
	TypeclassVirtual(VStar, times, a, b) = 0;
	// abs :: a -> a
	TypeclassVirtual(VStar, abs, value) = 0;
	// signum :: a -> a
	TypeclassVirtual(VStar, sign, value) = 0;
	// fromInteger :: Int -> a
	TypeclassVirtual(VStar, fromInt, integer) = 0;

	// negate :: a -> a
	TypeclassVirtual(VStar, negate, value) {
		VStar zero = fromInt()(IntV(0));
		return minus()(zero)(value);
	}
};