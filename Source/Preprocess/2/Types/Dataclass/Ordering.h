#pragma once

// UNUSED

// #include "Types/Show.h"



// #ifndef PP__PREPROCESSING

// #include "Types/VStar.h"

// #else

// include "Types/VStar.h"

// #endif

// #include "Types/FDecl.h"


// #define InlineStaticConstStruct(T, NAME, ...) \
// static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()
 



// class IBool : public virtual ITypeclass {
// private:
// 	virtual const Typeclass* _GetTypeclass() const override {
// 		return &IBool::Instances;
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
// 		$.Show = &IBool::ShowInst;
// 	);
// };





// class Bool : public virtual IBool {
// private:
// 	bool _value;

// 	friend IBool;
// public:
// 	virtual ~Bool() = default;

// 	Bool(bool value) : _value(value) {};
// 	Bool(const Bool& other) : _value(other._value) {};


// 	virtual bool get() const { return _value; }

// };

// inline FString IBool::Show::_show(const VStar& me) const {
// 	// Resolve
// 	bool a = me.ResolveToUnsafe<Bool>().get();
// }

// //SHOW((), Bool, ());