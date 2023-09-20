#pragma once

#include "Types/Ord.h"
#include "Types/Show.h"



#ifndef PP__PREPROCESSING

#include "Types/VStar.h"

#else

include "Types/VStar.h"

#endif

#include "Types/FDecl.h"


#define InlineStaticConstStruct(T, NAME, ...) \
static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()


#include "Types/Typeclass/Num_gen.h"
#include "Types/Typeclass/Eq_gen.h"
#include "Types/Typeclass/Enum_gen.h"
#include "Types/Typeclass/Bounded_gen.h"
#include "Types/Typeclass/Ordinal_gen.h"
#include "Types/Typeclass/Show_gen.h"
#include "Types/Typeclass/Read_gen.h"

NUM(Int);
EQ(Int);
ORDINAL(Int);
ENUM(Int);
BOUNDED(Int);
SHOW(Int);
READ(Int);




// TODO: Int





class IInt : public virtual ITypeclass {
private:
	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override {
		return NoopPtr(&IInt::Instances);
	}
public:
	INUM();
	// IEQ();
	IORDINAL();
	IENUM();
	IBOUNDED();
	ISHOW();
	// IREAD();
public:
	InlineStaticConstStruct(Typeclass, Instances,
		TypeclassInst(Int, Num);
		// TypeclassInst(Int, Eq);
		TypeclassInst(Int, Ordinal);
		TypeclassInstAs(Int, Ordinal, Eq);
		TypeclassInst(Int, Enum);
		TypeclassInst(Int, Bounded);
		TypeclassInst(Int, Show);
		// TypeclassInst(Int, Read);
	);
};





class Int : public virtual IInt {
private:
	int _value;

	friend IInt;

	friend IInt::Ordinal;
	friend IInt::Enum;
	friend IInt::Bounded;
	friend IInt::Show;
	friend IInt::Num;
public:
	virtual ~Int() = default;

	Int(int value) : _value(value) {};

	virtual int get() const { return _value; }
};

inline FString IInt::Show::_show(const VStar& me) const {
	// Resolve
	int a = me.ResolveToUnsafe<Int>().get();

	return FString::Format(TEXT("{0}"), { a });
}

inline ORD IInt::Ordinal::_ord( const VStar& a, const VStar& b) const {
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();

	return _a == _b ? ORD::EQ : _a < _b ? ORD::LT : ORD::GT;
}


virtual VStar IInt::Enum::_toEnum(const VStar& integer) const {
	return integer;
}	

virtual Int IInt::Enum::_fromEnum(const VStar& value) const {
	return value.ResolveToUnsafe<Int>();
}

virtual VStar IInt::Bounded::_minBound() const { return Int(INT_MIN); }
virtual VStar IInt::Bounded::_maxBound() const { return Int(INT_MAX); }

virtual VStar IInt::Num::_plus  ( const VStar& a , const VStar& b ) const 	{
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();
	return Int(_a + _b);
}

virtual VStar IInt::Num::_minus ( const VStar& a , const VStar& b ) const	{
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();
	return Int(_a - b);
}

virtual VStar IInt::Num::_times ( const VStar& a , const VStar& b ) const	{
	int _a = a.ResolveToUnsafe<Int>().get();
	int _b = b.ResolveToUnsafe<Int>().get();
	return Int(_a * _b);
}

virtual VStar IInt::Num::_abs   ( const VStar& value ) const				{
	int _a = value.ResolveToUnsafe<Int>().get();
	return Int(_a * _sign(_a));
}

virtual VStar IInt::Num::_sign  ( const VStar& value ) const				{
	int _a = value.ResolveToUnsafe<Int>().get();
	return Int((_a > 0) - (_a < 0));
}

virtual VStar IInt::Num::_fromInt ( const VStar& integer ) const		{
	return integer;
}