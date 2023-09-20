
#include "Functional/curry_gen.h"

#include "Functional/Prelude.h"

#include "Typeclass/Functor.h"
#include "Typeclass/Applicative.h"
#include "Typeclass/Monad.h"
#include "Typeclass/Semigroup.h"
#include "Typeclass/Monoid.h"
#include "Typeclass/Show.h"









class IFunc : public virtual ITypeclass {
private:
	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override;
public:
	class Functor;
	static const Functor FunctorInst;
	class Applicative;
	static const Applicative ApplicativeInst;
	class Monad;
	static const Monad MonadInst;

	class Semigroup;
	static const Semigroup SemigroupInst;
	class Monoid;
	static const Monoid MonoidInst;

	class Show;
	static const Show ShowInst;

public:
	static const Typeclass Instances;
};


class IFunc::Functor : public virtual IFunctor {
private:
	virtual VStar _fmap(const VStar& f, const VStar& f_a) const override;
public:
	Functor() = default;
};
const IFunc::Functor IFunc::FunctorInst = {};


class IFunc::Applicative : public virtual IApplicative {
private:
	virtual VStar _pure(const VStar& value) const override;						
	virtual VStar _apply(const VStar& boxedFunc, const VStar& app) const override;
public:
	Applicative() = default;
};
const IFunc::Applicative IFunc::ApplicativeInst = {};



class IFunc::Monad : public virtual IMonad {
private:
	virtual VStar _bind(const VStar& m_a, const VStar& a_to_mb) const override;
public:
	Monad() = default;
};
const IFunc::Monad IFunc::MonadInst = {};



class IFunc::Semigroup : public virtual ISemigroup {
private:
	virtual VStar _mappend( const VStar& left, const VStar& right) const override;
public:
	Semigroup() = default;
};
const IFunc::Semigroup IFunc::SemigroupInst = {};



class IFunc::Monoid : public virtual IMonoid {
private:
	virtual VStar _mempty() const override;
public:
	Monoid() = default;
};
const IFunc::Monoid IFunc::MonoidInst = {};



class IFunc::Show : public virtual IShow {
private:
	virtual FString _show(const VStar& a) const override;
public:
	Show() = default;
};
const IFunc::Show IFunc::ShowInst = {};








const TSharedPtr<Typeclass> IFunc::_GetTypeclass() const {
	return NoopPtr(&IFunc::Instances);
}

CppStaticConstStruct(Typeclass, IFunc::Instances,
	TypeclassInst(Func, Functor);
	TypeclassInst(Func, Applicative);
	TypeclassInst(Func, Monad);
	TypeclassInst(Func, Semigroup);
	TypeclassInst(Func, Monoid);
	TypeclassInst(Func, Show);
);


VStar IFunc::Functor::_fmap(const VStar& f, const VStar& g_a) const {
	// fmap for Arrows is (.)
	return PreludeV::compose(f)(g_a);

	// // Resolve Variables
	// ArrV g = f.ResolveToUnsafe<ArrV>();
	// ArrV f_a = g_a.ResolveToUnsafe<ArrV>();

	// // fmap for Arrows is (.)
	// return curry([g, f_a](const VStar& x) -> VStar {
	// 	return g(f_a(x));
	// });
}

// Non Canonical
FString IFunc::Show::_show(const VStar& a) const {
	return a.Type()->ToString();
}


inline VStar IFunc::Applicative::_pure(const VStar& value) const {
	// pure is const
	return PreludeV::constant(value);
	// return MaybeV::Just(value);
}	

inline VStar IFunc::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	ArrV f = boxedFunc.ResolveToUnsafe<ArrV>();
	ArrV g = app.ResolveToUnsafe<ArrV>();

	return curry([](const VStar &x) {
		return f(x)(g(x))
	});
}


inline  VStar IFunc::Monad::_bind(const VStar& m_a, const VStar& a_to_mb) const {
	// f >>= k = \ r -> k (f r) r
	ArrV f = m_a.ResolveToUnsafe<ArrV>();
	ArrV g = a_to_mb.ResolveToUnsafe<ArrV>();
	
	return curry([](const VStar &x) {
		return g(f(x))(x);
	});
}

inline VStar IFunc::Semigroup::_mappend( const VStar& left, const VStar& right) const {
	ArrV f = left.ResolveToUnsafe<ArrV>();
	ArrV g = right.ResolveToUnsafe<ArrV>();

	//\x -> f x <> g x
	return curry([](const VStar &x) {
		VStar fx = f(x);
		return fx.getTypeclass()->Semigroup->mappend()(fx)(g(x));
	});
}





inline VStar IFunc::Monoid::_mempty() const {
    //\_ -> mempty
	return curry([](const VStar &x) {
		return x.getTypeclass()->Semigroup->mempty();
	});
}






