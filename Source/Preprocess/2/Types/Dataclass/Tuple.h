#pragma once

// Currently Unused

// #include "Types/Show.h"



// #ifndef PP__PREPROCESSING

// #include "Types/VStar.h"

// #else

// include "Types/VStar.h"

// #endif

// #include "Types/FDecl.h"


// #define InlineStaticConstStruct(T, NAME, ...) \
// static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()
 


// #include "Types/Typeclass/Functor.h"
// #include "Types/Typeclass/Foldable.h"
// #include "Types/Typeclass/Traversable.h"
// #include "Types/Typeclass/Applicative.h"
// #include "Types/Typeclass/Monad.h"
// #include "Types/Typeclass/Eq.h"
// #include "Types/Typeclass/Ordinal.h"
// #include "Types/Typeclass/Bounded.h"
// #include "Types/Typeclass/Semigroup.h"
// #include "Types/Typeclass/Monoid.h"
// #include "Types/Typeclass/Show.h"
// #include "Types/Typeclass/Read.h"

// FUNCTOR(Tuple);

// FOLDABLE(Tuple);
// TRAVERSABLE(Tuple);


// // Dependant
// APPLICATIVE(Tuple);
// MONAD(Tuple);

// EQ(Tuple);
// ORDINAL(Tuple);
// BOUNDED(Tuple);

// SEMIGROUP(Tuple);
// MONOID(Tuple);

// SHOW(Tuple);
// READ(Tuple);




// class ITuple : public virtual ITypeclass {
// private:
// 	virtual const Typeclass* _GetTypeclass() const override {
// 		return &ITuple::Instances;
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
// 		$.Show = &ITuple::ShowInst;
// 	);
// };





// class Tuple : public virtual ITuple {
// private:
// 	bool _value;

// 	friend ITuple;
// public:
// 	virtual ~Tuple() = default;

// 	Tuple(bool value) : _value(value) {};
// 	Tuple(const Bool& other) : _value(other._value) {};


// 	virtual bool get() const { return _value; }

// };

// inline FString IBool::Show::_show(const VStar& me) const {
// 	// Resolve
// 	bool a = me.ResolveToUnsafe<Bool>().get();
// }

// //SHOW((), Bool, ());