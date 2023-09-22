#pragma once


#ifndef PP__PREPROCESSING

#include "Types/VStar.h"

#else

include "Types/VStar.h"

#endif

#include "Types/FDecl.h"


#define InlineStaticConstStruct(T, NAME, ...) \
static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()
 
#include "Types/Typeclass/Functor.h"
#include "Types/Typeclass/Applicative.h"
#include "Types/Typeclass/Monad.h"
#include "Types/Typeclass/Semigroup.h"
#include "Types/Typeclass/Foldable.h"
#include "Types/Typeclass/Traversable.h"
#include "Types/Typeclass/Eq.h"
#include "Types/Typeclass/Ordinal.h"
#include "Types/Typeclass/Show.h"
#include "Types/Typeclass/Read.h"

FUNCTOR(Either);
APPLICATIVE(Either);
MONAD(Either);
SEMIGROUP(Either);
FOLDABLE(Either);
TRAVERSABLE(Either);

// Dependant
EQ(Either);
ORDINAL(Either);
SHOW(Either);
READ(Either);


class IEither : public virtual ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
		return NoopPtr(&Instances);
	}
public:
    IFUNCTOR();
    IAPPLICATIVE();
    IMONAD();
    ISEMIGROUP();
    IFOLDABLE();
    ITRAVERSABLE();

    // Dependant
    // IEQ();
    IORDINAL();
    ISHOW();
    // IREAD();

public:
	InlineStaticConstStruct(Typeclass, Instances,
		TypeclassInst(Either, Functor);
		TypeclassInst(Either, Applicative);
		TypeclassInst(Either, Monad);
		TypeclassInst(Either, Semigroup);
		TypeclassInst(Either, Foldable);
		TypeclassInst(Either, Traversable);
		// TypeclassInst(Either, Eq);
		TypeclassInstAs(Either, Ordinal, Eq);
		TypeclassInst(Either, Ordinal);
		TypeclassInst(Either, Show);
		// TypeclassInst(Either, Read);
	);
};




template <typename Left, typename Right>
class Either : public virtual IEither {
private:
    VStar left;
    VStar right;

    friend IEither;

	friend IEither::Ordinal;
	friend IEither::Show;
	friend IEither::Functor;
	friend IEither::Applicative;
	friend IEither::Monad;
	friend IEither::Semigroup;
	friend IEither::Foldable;
	friend IEither::Traversable;

    Either(Left InLeft, bool ignored) : left(InLeft) {};
    Either(bool ignored, Right InRight) : right(InRight) {};

	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
        TSharedPtr<const Typeclass> inner = get().getTypeclass();
        TSharedPtr<Typeclass> out = MakeShareable(new Typeclass());
        *out = IEither::Instances;
        
        if (!inner->Ordinal) out->Ordinal = NULL;
        if (!inner->Eq) out->Eq = NULL;
        if (!inner->Show) out->Show = NULL;

        return out;
	}
public:
	virtual ~Either() = default;

public:
    static Either<Left, Right> AsLeft(Left InLeft) {
        return Either<Left, Right>(InLeft, false);
    }
    static Either<Left, Right> AsRight(Right InRight) {
        return Either<Left, Right>(false, InRight);
    }


public:
    Bool isLeft() const {
        return left.Valid();
    }
    Bool isRight() const {
        return right.Valid();
    };

    Left fromLeft(Left fallback) const {
        return isLeft().get() ? left.ResolveToUnsafe<Left>() : fallback;
    }
    Right fromRight(Right fallback) const {
        return isRight().get() ? right.ResolveToUnsafe<Right>() : fallback;
    }

    VStar get() const {
        return isLeft().get() ? left : right;
    }

	// Cast Construction
	Either(const EitherV* other);
};

template <>
class Either<VStar, VStar> : public virtual IEither {
private:
    VStar left;
    VStar right;

    friend IEither;

	friend IEither::Ordinal;
	friend IEither::Show;
	friend IEither::Functor;
	friend IEither::Applicative;
	friend IEither::Monad;
	friend IEither::Semigroup;
	friend IEither::Foldable;
	friend IEither::Traversable;

	template <typename Left, typename Right>
	friend Either<Left, Right>::Either(const EitherV* other);

    Either(VStar InLeft, bool ignored) : left(InLeft) {};
    Either(bool ignored, VStar InRight) : right(InRight) {};
public:
	virtual ~Either() = default;

public:
    static EitherV AsLeft(VStar InLeft) {
        return EitherV(InLeft, false);
    }
    static EitherV AsRight(VStar InRight) {
        return EitherV(false, InRight);
    }

public:
    Bool isLeft() const {
        return left.Valid();
    }
    Bool isRight() const {
        return right.Valid();
    };

    template <typename Left>
    Left fromLeft(Left fallback) const {
        return isLeft().get() ? left.ResolveToUnsafe<Left>() : fallback;
    }
    template <>
    VStar fromLeft(VStar fallback) const {
        return isLeft().get() ? left : fallback;
    }

    template <typename Right>
    Right fromRight(Right fallback) const {
        return isRight().get() ? right.ResolveToUnsafe<Right>() : fallback;
    }
    template <>
    VStar fromRight(VStar fallback) const {
        return isRight().get() ? right : fallback;
    }

    VStar get() const {
        return isLeft().get() ? left : right;
    }
}; 

template <typename Left, typename Right>
Either<Left, Right>::Either(const EitherV* other) {
    if (other->isLeft().get()) {
        left = other->get().ResolveToUnsafe<Left>();
    } else {
        right = other->get().ResolveToUnsafe<Right>();
    }
}



template <typename L, typename R>
auto isLeft = curry([](Either<L,R> l_a) -> Bool {
    return l_a.isLeft();
});

template <typename L, typename R>
auto isRight = curry([](Either<L,R> l_a) -> Bool {
    return l_a.isRight();
});

template <typename L, typename R>
auto fromLeft = curry([](Either<L,R> l_a, L a) -> L {
    return l_a.fromLeft(a);
});

template <typename L, typename R>
auto fromRight = curry([](Either<L,R> l_a, R a) -> R {
    return l_a.fromRight(a);
});


inline FString IEither::Show::_show(const VStar& me) const {
	// Resolve
	EitherV a = me.ResolveToUnsafe<EitherV>();

    return FString(a.isLeft().get() ? "L:" : "R:") + a.get().getTypeclass()->Show->show()(a.get());
}

//SHOW((), Bool, ());


inline ORD IEither::Ordinal::_ord( const VStar& a, const VStar& b) const {
	EitherV _a = a.ResolveToUnsafe<EitherV>();
	EitherV _b = b.ResolveToUnsafe<EitherV>();

    // Left < Right, check for both sides
    if (_a.isLeft().get() && _b.isRight().get()) return ORD::LT;
    if (_a.isRight().get() && _b.isLeft().get()) return ORD::GT;
    
    // Handle equal case
    return _a.get().getTypeclass()->Ordinal->ord()(_a.get())(_b.get());
}


inline VStar IEither::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	// Resolve Variables
	EitherV m_a = f_a.ResolveToUnsafe<EitherV>();

    // Left is no op
    if (m_a.isLeft().get()) return m_a;

    // Right is op
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return EitherV::AsRight(g(m_a.get()));
}

inline VStar IEither::Applicative::_pure(const VStar& value) const {
    return EitherV::AsRight(value);
}	

inline VStar IEither::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	EitherV m_a = boxedFunc.ResolveToUnsafe<EitherV>();

    // left is no op
	if (m_a.isLeft().get()) return m_a;

    // right is op
    return app.getTypeclass()->Functor->fmap()(m_a.get())(app);
}

inline  VStar IEither::Monad::_bind(const VStar& m_a, const VStar& a_to_mb) const {
	EitherV _ma = m_a.ResolveToUnsafe<EitherV>();

	if (_ma.isLeft().get()) return _ma;

	ArrV arr = a_to_mb.ResolveToUnsafe<ArrV>();
	return arr(_ma.get());
}

inline VStar IEither::Foldable::_foldr(const VStar& f, const VStar& initial, const VStar& foldable) const {
    EitherV _ma = foldable.ResolveToUnsafe<EitherV>();

    // left is initial
    if (_ma.isLeft().get()) return initial;

    // right is apply transformation
	ArrV g = f.ResolveToUnsafe<ArrV>();

    return g(_ma.get()).ResolveToUnsafe<ArrV>()(initial);
}

inline VStar IEither::Traversable::_traverse(const VStar& applic, const VStar& f, const VStar& foldable) const {
    EitherV _ma = foldable.ResolveToUnsafe<EitherV>();

    // const IApplicative* applic = foldable.getType().getTemplates()[0]

    // _ (Left x) -> pure (Left x)
    if (_ma.isLeft().get()) {
        return applic.getTypeclass()->Applicative->pure()(EitherV::AsLeft(_ma.get()));
    }

    // f (Right y) -> Right <$> f y
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return _ma.get().getTypeclass()->Functor->fmap()(ArrV(EitherV::AsRight))(g(_ma.get()));
}
 
inline VStar IEither::Semigroup::_mappend( const VStar& left, const VStar& right) const {
    EitherV _ma = left.ResolveToUnsafe<EitherV>();

    // Left is use other
    if (_ma.isLeft().get()) return right;
    // Right is use me
    return _ma;
}