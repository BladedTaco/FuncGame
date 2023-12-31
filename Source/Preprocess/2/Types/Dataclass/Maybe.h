#pragma once

#include "Types/FDecl.h"

 
#ifndef PP__PREPROCESSING

#include "Misc/Optional.h"

#else

include "Misc/Optional.h"

#endif


#include "Types/Typeclass/Functor.h"
#include "Types/Typeclass/Applicative.h"
#include "Types/Typeclass/Monad.h"
#include "Types/Typeclass/Semigroup.h"
#include "Types/Typeclass/Monoid.h"
#include "Types/Typeclass/Foldable.h"
#include "Types/Typeclass/Traversable.h"
#include "Types/Typeclass/Alternative.h"
#include "Types/Typeclass/Eq.h"
#include "Types/Typeclass/Ordinal.h"
#include "Types/Typeclass/Show.h"
#include "Types/Typeclass/Read.h"

FUNCTOR(Maybe);
APPLICATIVE(Maybe);
MONAD(Maybe);


FOLDABLE(Maybe);
TRAVERSABLE(Maybe);

ALTERNATIVE(Maybe);

// Dependant
SEMIGROUP(Maybe);
MONOID(Maybe);

EQ(Maybe);
ORDINAL(Maybe);
SHOW(Maybe);
READ(Maybe);


class IMaybe : public virtual ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
		return NoopPtr(&Instances);
	}
public:
	IFUNCTOR(Maybe);
	IAPPLICATIVE(Maybe);
	IMONAD(Maybe);
	IFOLDABLE(Maybe);
	ITRAVERSABLE(Maybe);
	// IALTERNATIVE(Maybe);
	// Dependant
	ISEMIGROUP(Maybe);
	IMONOID(Maybe);
	// IEQ(Maybe);
	IORDINAL(Maybe);
	ISHOW(Maybe);
	// IREAD(Maybe);

public:
	InlineStaticConstStruct(Typeclass, Instances,
		TypeclassInst(Maybe, Functor);
		TypeclassInst(Maybe, Applicative);
		TypeclassInst(Maybe, Monad);
		TypeclassInst(Maybe, Foldable);
		TypeclassInst(Maybe, Traversable);
		// TypeclassInst(Maybe, Alternative);
		TypeclassInst(Maybe, Semigroup);
		TypeclassInst(Maybe, Monoid);
		// TypeclassInst(Maybe, Eq);
		TypeclassInst(Maybe, Ordinal);
		TypeclassInstAs(Maybe, Ordinal, Eq);
		TypeclassInst(Maybe, Show);
		// TypeclassInst(Maybe, Read);
	);
};




// Functor Maybe
template <typename A>
class Maybe : public virtual IMaybe {
private:
	bool _isNothing;
	TOptional<A> _value;
	Maybe() {
		_isNothing = true;
	}
	Maybe(A a) {
		_isNothing = false;
		_value = a;
	}
	friend IMaybe::Functor;
	friend IMaybe::Show;
	friend IMaybe::Ordinal;
	friend class ::Functor<Maybe<A>>;
	friend MaybeV;

	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
        if (_isNothing) return NoopPtr(&Instances);

		// Copy
        TSharedPtr<Typeclass> out = MakeShareable(new Typeclass());
        *out = IMaybe::Instances;

		// Change based on inner
        TSharedPtr<const Typeclass> inner = _value->GetTypeclass();
        if (!inner->Semigroup) out->Semigroup = NULL;
        if (!inner->Monoid) out->Monoid = NULL;
        if (!inner->Ordinal) out->Ordinal = NULL;
        if (!inner->Eq) out->Eq = NULL;
        if (!inner->Show) out->Show = NULL;

        return out;
	}

public:
	virtual ~Maybe() = default;

	static Maybe<A> Just(A a) {
		return Maybe<A>(a);
	}
	static Maybe<A> Nothing() {
		return Maybe<A>();
	}
public:
	A fromMaybe(A fallback) {
		if (_isNothing) {
			return fallback;
		} else {
			return _value.GetValue();
		}
	}

	// Cast Construction
	Maybe(const MaybeV* other);
};


// Functor Maybe
template <>
class Maybe<VStar> : public virtual IMaybe {
private:

	friend VStar;
	friend Maybe;
	friend class ATypeRepr;

	friend IMaybe::Ordinal;
	friend IMaybe::Show;
	friend IMaybe::Functor;
	friend IMaybe::Applicative;
	friend IMaybe::Monad;
	friend IMaybe::Monoid;
	friend IMaybe::Semigroup;
	friend IMaybe::Foldable;
	friend IMaybe::Traversable;

	template <typename A>
	friend Maybe<A>::Maybe(const MaybeV* other);

	bool _isNothing;
	VStar _value;


	Maybe() {
		_isNothing = true;
	}

	Maybe(VStar from) {
		_isNothing = false;
		_value = from;
	}

	friend class ::Functor<MaybeV>;
public:
	virtual ~Maybe() = default;

	template <typename A>
	static MaybeV Just(A a) {
		return MaybeV(VStar(a));
	}
	template <>
	static MaybeV Just(VStar a) {
		return MaybeV(a);
	}

	static MaybeV Nothing() {
		return MaybeV();
	}

public:
	template <typename A>
	A fromMaybe(A fallback) {
		if (_isNothing) {
			return fallback;
		} else {
			return _value.ResolveToUnsafe<A>();
		}
	}
	template <>
	VStar fromMaybe(VStar fallback) {
		if (_isNothing) {
			return fallback;
		} else {
			return _value;
		}
	}
};

template <typename A>
Maybe<A>::Maybe(const MaybeV* other) {
	_isNothing = other->_isNothing;
	if (!_isNothing) {
		_value = other->_value.ResolveToUnsafe<A>();
	}
}



template <typename A>
auto fromMaybe = curry([](A a, Maybe<A> m_a) -> A {
	return m_a.fromMaybe(a);
});


 

inline VStar IMaybe::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	// Resolve Variables
	ArrV g = f.ResolveToUnsafe<ArrV>();
	MaybeV m_a = f_a.ResolveToUnsafe<MaybeV>();

	// Logic
	if (m_a._isNothing) {
		return VStar(MaybeV::Nothing());
	} else {
		VStar result = g(m_a._value);
		return VStar(MaybeV::Just(result));
	}
}

inline VStar IMaybe::Applicative::_pure(const VStar& value) const {
	return MaybeV::Just(value);
}	

inline VStar IMaybe::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	MaybeV m_a = boxedFunc.ResolveToUnsafe<MaybeV>();

	if (m_a._isNothing) return MaybeV::Nothing();
	return app.getTypeclass()->Functor->fmap()(m_a._value)(app);
}

inline  VStar IMaybe::Monad::_bind(const VStar& m_a, const VStar& a_to_mb) const {
	MaybeV _ma = m_a.ResolveToUnsafe<MaybeV>();

	if (_ma._isNothing) return MaybeV::Nothing();

	ArrV arr = a_to_mb.ResolveToUnsafe<ArrV>();
	return arr(_ma._value);
}


inline FString IMaybe::Show::_show(const VStar& a) const {
	// Resolve Variables
	MaybeV m_a = a.ResolveToUnsafe<MaybeV>();

	// Logic
	if (m_a._isNothing) {
		return FString(TEXT("Nothing"));
	} else {
		FString inner = m_a._value.getTypeclass()->Show->show()(m_a._value);
		return FString(TEXT("Just ")) + inner;
	}
}


inline ORD IMaybe::Ordinal::_ord( const VStar& a, const VStar& b) const {
	MaybeV _a = a.ResolveToUnsafe<MaybeV>();
	MaybeV _b = b.ResolveToUnsafe<MaybeV>();

    // Nothing is smaller than Just
	if (_a._isNothing || _b._isNothing) return ORD(_b._isNothing - _a._isNothing);

	// Compare Justs
	return _a._value.getTypeclass()->Ordinal->ord()(_a._value)(_b._value);
}


inline VStar IMaybe::Foldable::_foldr(const VStar& f, const VStar& initial, const VStar& foldable) const {
    MaybeV _ma = foldable.ResolveToUnsafe<MaybeV>();

    // left is initial
    if (_ma._isNothing) return initial;

    // right is apply transformation
	ArrV g = f.ResolveToUnsafe<ArrV>();

    return g(_ma._value).ResolveToUnsafe<ArrV>()(initial);
}

inline VStar IMaybe::Traversable::_traverse( const VStar& applic, const VStar& f, const VStar& foldable) const {
    MaybeV _ma = foldable.ResolveToUnsafe<MaybeV>();

    // _  Nothing -> pure Nothing
    if (_ma._isNothing) {
        return applic.getTypeclass()->Applicative->pure()(MaybeV::Nothing());
    }

    // f (Just y) -> Just <$> f y
	ArrV g = f.ResolveToUnsafe<ArrV>();

	VStar h = VStar(curry([](const VStar& x) { return MaybeV::Just(x); }));

    return _ma._value.getTypeclass()->Functor->fmap()(h)(g(_ma._value));
}


inline VStar IMaybe::Semigroup::_mappend( const VStar& left, const VStar& right) const {
    MaybeV ma = left.ResolveToUnsafe<MaybeV>();
    MaybeV mb = left.ResolveToUnsafe<MaybeV>();

    // If one is nothing return the other
    if (ma._isNothing) return mb;
	if (mb._isNothing) return ma;

	// else mappend inners
	return MaybeV::Just(ma._value.getTypeclass()->Semigroup->mappend()(ma._value)(mb._value));
}

inline VStar IMaybe::Monoid::_mempty() const {
    return MaybeV::Nothing();
}