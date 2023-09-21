#pragma once


#ifndef PP__PREPROCESSING

#include "Types/VStar.h"

#else

include "Types/VStar.h"

#endif

#include "Types/FDecl.h"


#define InlineStaticConstStruct(T, NAME, ...) \
static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()


#include "Types/Typeclass/Num.h"
#include "Types/Typeclass/Eq.h"
#include "Types/Typeclass/Enum.h"
#include "Types/Typeclass/Bounded.h"
#include "Types/Typeclass/Ordinal.h"
#include "Types/Typeclass/Show.h"
#include "Types/Typeclass/Read.h"

NUM(BASE_Int);
EQ(BASE_Int);
ORDINAL(BASE_Int);
ENUM(BASE_Int);
BOUNDED(BASE_Int);
SHOW(BASE_Int);
READ(BASE_Int);




// TODO: Int





class IInt : public virtual ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
		return NoopPtr(&Instances);
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