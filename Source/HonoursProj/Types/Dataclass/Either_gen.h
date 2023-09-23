﻿// ---------------------------------------------------------------------------------------
// This File (Either_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "Types/VStar.h"
#include "Types\FDecl.h"
#include "Types\Typeclass\Functor.h"
#include "Types\Typeclass\Applicative.h"
#include "Types\Typeclass\Monad.h"
#include "Types\Typeclass\Semigroup.h"
#include "Types\Typeclass\Foldable.h"
#include "Types\Typeclass\Traversable.h"
#include "Types\Typeclass\Eq.h"
#include "Types\Typeclass\Ordinal.h"
#include "Types\Typeclass\Show.h"
#include "Types\Typeclass\Read.h"

 /*Added Typeclass Functor Instance Either*/ 
 ;

 /*Added Typeclass Applicative Instance Either*/ 
 ;

 /*Added Typeclass Monad Instance Either*/ 
 ;

 /*Added Typeclass Semigroup Instance Either*/ 
 ;

 /*Added Typeclass Foldable Instance Either*/ 
 ;

 /*Added Typeclass Traversable Instance Either*/ 
 ;

 /*Added Typeclass Eq Instance Either*/ 
 ;

 /*Added Typeclass Ordinal Instance Either*/ 
 ;

 /*Added Typeclass Show Instance Either*/ 
 ;

 /*Added Typeclass Read Instance Either*/ 
 ;
class IEither : public virtual ITypeclass {
private:
	virtual TSharedPtr<const Typeclass> _GetTypeclass() const override {
		return NoopPtr(&Instances);
	}
public:
    
 class Functor : public virtual IFunctor { 
 private: 
 virtual VStar _fmap(const VStar& f, const VStar& f_a) const override; 
 public: 
 Functor() = default; 
 }; 
 inline static const Functor FunctorInst = {}; ;
    
 class Applicative : public virtual IApplicative, public virtual Functor { 
 private: 
 virtual VStar _pure(const VStar& value) const override; 
 virtual VStar _apply(const VStar& boxedFunc, const VStar& app) const override; 
 public: 
 Applicative() = default; 
 }; 
 inline static const Applicative ApplicativeInst = {}; ;
    
 class Monad : public virtual IMonad, public virtual Applicative { 
 private: 
 virtual VStar _bind(const VStar& m_a, const VStar& a_to_mb) const override; 
 public: 
 Monad() = default; 
 }; 
 inline static const Monad MonadInst = {}; ;
    
 class Semigroup : public virtual ISemigroup { 
 private: 
 virtual VStar _mappend( const VStar& left, const VStar& right) const override; 
 public: 
 Semigroup() = default; 
 }; 
 inline static const Semigroup SemigroupInst = {}; ;
    
 class Foldable : public virtual IFoldable { 
 private: 
 virtual VStar _foldr(const VStar& f, const VStar& initial, const VStar& foldable) const override; 
 public: 
 Foldable() = default; 
 }; 
 inline static const Foldable FoldableInst = {}; ;
    
 class Traversable : public virtual ITraversable, public virtual Foldable, public virtual Functor { 
 private: 
 virtual VStar _traverse(const VStar& applic, const VStar& f, const VStar& foldable) const override; 
 public: 
 Traversable() = default; 
 }; 
 inline static const Traversable TraversableInst = {}; ;
    
 class Ordinal : public virtual IOrdinal { 
 private: 
 virtual ORD _ord( const VStar& a, const VStar& b) const override; 
 public: 
 Ordinal() = default; 
 }; 
 inline static const Ordinal OrdinalInst = {}; ;
    
 class Show : public virtual IShow { 
 private: 
 virtual FString _show( const VStar& me) const override; 
 public: 
 Show() = default; 
 }; 
 inline static const Show ShowInst = {}; ;
public:
	static const inline Typeclass Instances = []{ Typeclass ${}; $.Functor = &IEither::FunctorInst; $.Applicative = &IEither::ApplicativeInst; $.Monad = &IEither::MonadInst; $.Semigroup = &IEither::SemigroupInst; $.Foldable = &IEither::FoldableInst; $.Traversable = &IEither::TraversableInst; $.Eq = &IEither::OrdinalInst; $.Ordinal = &IEither::OrdinalInst; $.Show = &IEither::ShowInst;; return $; }()
;
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
    template <typename L>
    static EitherV AsLeft(L InLeft) {
        return EitherV(VStar(InLeft), false);
    }
    template <>
    static EitherV AsLeft(VStar InLeft) {
        return EitherV(InLeft, false);
    }
    template <typename R>
    static EitherV AsRight(R InRight) {
        return EitherV(false, VStar(InRight));
    }
    template <>
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
	EitherV a = me.ResolveToUnsafe<EitherV>();
    return FString(a.isLeft().get() ? "L:" : "R:") + a.get().getTypeclass()->Show->show()(a.get());
}
inline ORD IEither::Ordinal::_ord( const VStar& a, const VStar& b) const {
	EitherV _a = a.ResolveToUnsafe<EitherV>();
	EitherV _b = b.ResolveToUnsafe<EitherV>();
    if (_a.isLeft().get() && _b.isRight().get()) return ORD::LT;
    if (_a.isRight().get() && _b.isLeft().get()) return ORD::GT;
    return _a.get().getTypeclass()->Ordinal->ord()(_a.get())(_b.get());
}
inline VStar IEither::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	EitherV m_a = f_a.ResolveToUnsafe<EitherV>();
    if (m_a.isLeft().get()) return m_a;
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return EitherV::AsRight(g(m_a.get()));
}
inline VStar IEither::Applicative::_pure(const VStar& value) const {
    return EitherV::AsRight(value);
}	
inline VStar IEither::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	EitherV m_a = boxedFunc.ResolveToUnsafe<EitherV>();
	if (m_a.isLeft().get()) return m_a;
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
    if (_ma.isLeft().get()) return initial;
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return g(_ma.get()).ResolveToUnsafe<ArrV>()(initial);
}
inline VStar IEither::Traversable::_traverse(const VStar& applic, const VStar& f, const VStar& foldable) const {
    EitherV _ma = foldable.ResolveToUnsafe<EitherV>();
    if (_ma.isLeft().get()) {
        return applic.getTypeclass()->Applicative->pure()(EitherV::AsLeft(_ma.get()));
    }
    ArrV right = curry([](VStar a) -> VStar { return VStar(EitherV::AsRight(a));});
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return _ma.get().getTypeclass()->Functor->fmap()(right)(g(_ma.get()));
}
inline VStar IEither::Semigroup::_mappend( const VStar& left, const VStar& right) const {
    EitherV _ma = left.ResolveToUnsafe<EitherV>();
    if (_ma.isLeft().get()) return right;
    return _ma;
}
