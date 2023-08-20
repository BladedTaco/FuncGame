
#include "Functional/curry_gen.h"

#include "Functor.h"
#include "Show.h"

class IFunc::Functor : public virtual IFunctor {
private:
	virtual VStar _fmap(const VStar& f, const VStar& f_a) const override;
public:
	Functor() = default;
};
const IFunc::Functor IFunc::FunctorInst = {};


class IFunc::Show : public virtual IShow {
private:
	virtual FString _show(const VStar& a) const override;
public:
	Show() = default;
};
const IFunc::Show IFunc::ShowInst = {};


const Typeclass* IFunc::_GetTypeclass() const {
	return &IFunc::Instances;
}

CppStaticConstStruct(Typeclass, IFunc::Instances,
	$.Functor = &IFunc::FunctorInst;
	$.Show = &IFunc::ShowInst;
);


VStar IFunc::Functor::_fmap(const VStar& f, const VStar& g_a) const {
	// Resolve Variables
	ArrV g = f.ResolveToUnsafe<ArrV>();
	ArrV f_a = g_a.ResolveToUnsafe<ArrV>();

	// fmap for Arrows is (.)
	return curry([g, f_a](const VStar& x) -> VStar {
		return g(f_a(x));
	});
}


FString IFunc::Show::_show(const VStar& a) const {
	return a.Type()->ToString();
}