#pragma once

#include "Types/Show.h"



#ifndef PP__PREPROCESSING

#include "Types/VStar.h"

#else

include "Types/VStar.h"

#endif

#include "Types/FDecl.h"


#define InlineStaticConstStruct(T, NAME, ...) \
static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()

#include "Types/Typeclass/Eq_gen.h"
#include "Types/Typeclass/Ordinal_gen.h"
#include "Types/Typeclass/Enum_gen.h"
#include "Types/Typeclass/Bounded_gen.h"
#include "Types/Typeclass/Show_gen.h"
#include "Types/Typeclass/Read_gen.h"

EQ(Bool);
ORDINAL(Bool);
ENUM(Bool);
BOUNDED(Bool);
SHOW(Bool);
READ(Bool);

class IBool : public virtual ITypeclass {
private:
	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override {
		return NoopPtr(&IBool::Instances);
	}
public:
	// IEQ();
	IORDINAL();
	IENUM();
	IBOUNDED();
	ISHOW();
	// IREAD();
public:
	InlineStaticConstStruct(Typeclass, Instances,
		TypeclassInst(Bool, Ordinal);
		TypeclassInstAs(Bool, Ordinal, Eq);
		TypeclassInst(Bool, Enum);
		TypeclassInst(Bool, Bounded);
		TypeclassInst(Bool, Show);
		// TypeclassInst(Bool, Read);
	);
};





class Bool : public virtual IBool {
private:
	bool _value;

	friend IBool;

	friend IBool::Ordinal;
	friend IBool::Enum;
	friend IBool::Bounded;
	friend IBool::Show;

public:
	virtual ~Bool() = default;

	Bool(bool value) : _value(value) {};
	Bool(const Bool& other) : _value(other._value) {};


	virtual bool get() const { return _value; }

};

inline FString IBool::Show::_show(const VStar& me) const {
	// Resolve
	bool a = me.ResolveToUnsafe<Bool>().get();
	return a ? FString(TEXT("✓")) : FString(TEXT("X"));
}


inline ORD IBool::Ordinal::_ord( const VStar& a, const VStar& b) const {
	bool _a = a.ResolveToUnsafe<Bool>().get();
	bool _b = b.ResolveToUnsafe<Bool>().get();

	return _a == _b ? ORD::EQ : _b ? ORD::LT : ORD::GT;
}

virtual VStar IBool::Enum::_toEnum(const VStar& integer) const {
	int a = integer.ResolveToUnsafe<Int>().get();
	return Bool(a != 0);
}	

virtual Int IBool::Enum::_fromEnum(const VStar& value) const {
	bool a = value.ResolveToUnsafe<Bool>().get();
	return Int(a ? 1 : 0);
}

virtual VStar IBool::Bounded::_minBound() const { return Bool(false); }
virtual VStar IBool::Bounded::_maxBound() const { return Bool(true); }