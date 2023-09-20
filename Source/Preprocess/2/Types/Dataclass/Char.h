#pragma once

// UNUSED

// // Typeclasses
// #include "Types/Show.h"



// #ifndef PP__PREPROCESSING

// #include "Types/VStar.h"

// #else

// include "Types/VStar.h"

// #endif

// // Forward Declarations
// #include "Types/FDecl.h"


// #define InlineStaticConstStruct(T, NAME, ...) \
// static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()
 


// class IChar : public virtual ITypeclass {
// private:
// 	virtual const Typeclass* _GetTypeclass() const override {
// 		return &IChar::Instances;
// 	}
// public:
// 	class Show : public virtual IShow {
// 	private:
// 		virtual FString _show(const VStar& me) const override;
// 	public:
// 		Show() = default;
// 	};
// 	inline static const Show ShowInst = {};

// public:
// 	InlineStaticConstStruct(Typeclass, Instances,
// 		$.Show = &IChar::ShowInst;
// 	);
// };





// class Char : public virtual IChar {
// private:
// 	bool _value;

// 	friend IBool;
// public:
// 	virtual ~Bool() = default;

// 	Bool(bool value) : _value(value) {};
// 	Bool(const Bool& other) : _value(other._value) {};


// 	virtual bool get() const { return _value; }

// };

// inline FString IChar::Show::_show(const VStar& me) const {
// 	// Resolve
// 	bool a = me.ResolveToUnsafe<Bool>().get();

// 	return a ? FString(TEXT("✓")) : FString(TEXT("X"));
// }

// //SHOW((), Bool, ());