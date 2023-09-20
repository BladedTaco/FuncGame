#pragma once

#include "Types/Functor.h"
#include "Types/Show.h"
 
#include "Types/FDecl.h"

 
#ifndef PP__PREPROCESSING

#include "Misc/Optional.h"

#else

include "Misc/Optional.h"

#endif

#include "Types/Typeclass/Functor_gen.h"
#include "Types/Typeclass/Applicative_gen.h"
#include "Types/Typeclass/Monad_gen.h"
#include "Types/Typeclass/Semigroup_gen.h"
#include "Types/Typeclass/Monoid_gen.h"
#include "Types/Typeclass/Foldable_gen.h"
#include "Types/Typeclass/Traversable_gen.h"
#include "Types/Typeclass/Alternative_gen.h"
#include "Types/Typeclass/Eq_gen.h"
#include "Types/Typeclass/Ordinal_gen.h"
#include "Types/Typeclass/Show_gen.h"
#include "Types/Typeclass/Read_gen.h"

FUNCTOR(List);
APPLICATIVE(List);
MONAD(List);

SEMIGROUP(List);
MONOID(List);

FOLDABLE(List);
TRAVERSABLE(List);

ALTERNATIVE(List);

// Dependant
EQ(List);
ORDINAL(List);
SHOW(List);
READ(List);



class IList : public virtual ITypeclass {
private:
	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override {
		return NoopPtr(&IList::Instances);
	}
public:
	IFUNCTOR(List);
    IAPPLICATIVE(List);
    IMONAD(List);

    ISEMIGROUP(List);
    IMONOID(List);

    IFOLDABLE(List);
    ITRAVERSABLE(List);

    // IALTERNATIVE(List);

    // Dependant
    // IEQ(List);
    IORDINAL(List);
    ISHOW(List);
    // IREAD(List);

public:
	InlineStaticConstStruct(Typeclass, Instances,
		TypeclassInst(List, Functor);
		TypeclassInst(List, Applicative);
		TypeclassInst(List, Monad);
		TypeclassInst(List, Semigroup);
		TypeclassInst(List, Monoid);
		TypeclassInst(List, Foldable);
		TypeclassInst(List, Traversable);
		// TypeclassInst(List, Alternative);
		// TypeclassInst(List, Eq);
		TypeclassInstAs(List, Ordinal, Eq);
		TypeclassInst(List, Ordinal);
		TypeclassInst(List, Show);
		// TypeclassInst(List, Read);
	);
};




// Functor Maybe
template <typename A>
class List : public virtual IList {
private:
    VStar _head;
    VStar _rest;
    VStar _next;

	friend IList::Ordinal;
	friend IList::Show;
	friend IList::Functor;
	friend IList::Applicative;
	friend IList::Monad;
	friend IList::Monoid;
	friend IList::Semigroup;
	friend IList::Foldable;
	friend IList::Traversable;
	friend ListV;

	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override {
        // No Instance Retains all Typeclasses
        if (isEmpty().get()) return IList::_GetTypeclass(); 

        // Copy
        TSharedPtr<Typeclass> out = MakeShared();
        *out = IEither::Instances;
        
        // Change
        const Typeclass* inner = _head.getTypeclass();
        if (!inner->Ordinal) out->Ordinal = NULL;
        if (!inner->Eq) out->Eq = NULL;
        if (!inner->Show) out->Show = NULL;

        return out;
	}
public:
	virtual ~List() = default;

    List(){};
    List(A InHead, List<A> InRest)
        : _head(InHead)
        , _rest(InRest)
    {};
    List(A seed, Arr<A, A> InNext)
        : _head(seed)
        , _next(InNext)
    {};

public:
    Bool isEmpty() { return !_head.Valid(); }
    Bool isInfinite() { return _next.Valid(); }
    A head(A fallback) {
        return isEmpty() ? fallback : _head.ResolveToUnsafe<A>();
	}
    List<A> rest() {
        // strict list
        if (_rest.Valid()) return _rest.ResolveToUnsafe<List<A>>();
        // No Next
        if (!_next.Valid()) return List();
        // Generate next
        return List(_next(_head), _next);
    }

	// Cast Construction
	List(const ListV* other);
};


// Functor Maybe
template <>
class List<VStar> : public virtual IList {
private:
    VStar _head;
    VStar _rest;
    VStar _next;

	friend IList::Ordinal;
	friend IList::Show;
	friend IList::Functor;
	friend IList::Applicative;
	friend IList::Monad;
	friend IList::Semigroup;
	friend IList::Foldable;
	friend IList::Traversable;
	friend ListV;

	template <typename A>
	friend List<A>::List(const ListV* other);
public:
	virtual ~List() = default;

    List(){};
    List(VStar InHead, ListV InRest)
        : _head(InHead)
        , _rest(InRest)
    {};
    List(VStar seed, Arr<A, A> InNext)
        : _head(seed)
        , _next(InNext)
    {};

public:
    Bool isEmpty() { return !_head.Valid(); }
    Bool isInfinite() { return _next.Valid(); }
    template <typename A>
    A head(A fallback) {
        return isEmpty() ? fallback : _head.ResolveToUnsafe<A>();
	}
    template <>
    VStar head(VStar fallback) {
        return isEmpty() ? fallback : _head;
	}
    template <typename A>
    List<A> rest() {
        // strict list
        if (_rest.Valid()) return _rest.ResolveToUnsafe<List<A>>();
        // No Next
        if (!_next.Valid()) return List();
        // Generate next
        return List(_next(_head), _next);
    }
    template <>
    ListV rest() {
        // strict list
        if (_rest.Valid()) return _rest.ResolveToUnsafe<ListV>();
        // No Next
        if (!_next.Valid()) return ListV();
        // Generate next
        return ListV(_next(_head), _next);
    }

	// Cast Construction
	List(const ListV* other);
};

template <typename A>
List<A>::List(const ListV* other) {
    _head = other->_head;
    _rest = other->_rest;
    _next = other->_next;
}

template <typename A>
auto isEmpty = curry([](List<A> l_a) -> Bool {
    return l_a.isEmpty();
});

template <typename A>
auto isInfinite = curry([](List<A> l_a) -> Bool {
    return l_a.isInfinite();
});

template <typename A>
auto head = curry([](List<A> l_a, A a) -> A {
    return l_a.head(a);
});

template <typename A>
auto rest = curry([](List<A> l_a, A a) -> A {
    return l_a.rest(a);
});

template <typename A>
auto cons = curry([](A head, List<A> list) {
    return List<A>(head, list);
});

inline FString IList::Show::_show(const VStar& a) const {
	// Resolve Variables
	ListV m_a = a.ResolveToUnsafe<ListV>();

	// Logic
	return m_a.isEmpty()
		? FString(TEXT("[]"));
        : FString::Format(TEXT("[{0}, ...]"), { m_a._head.getTypeclass()->Show->show()(m_a._head) });
}





inline ORD IList::Ordinal::_ord( const VStar& a, const VStar& b) const {
	ListV _a = a.ResolveToUnsafe<ListV>();
	ListV _b = b.ResolveToUnsafe<ListV>();

    // Empty list is Smaller than Non-empty
    int _ae = _a.isEmpty().get();
    int _be = _b.isEmpty().get();
    if (_ae || _be) return ORD(_be - _ae);

    // Compare and recurse
    ORD order = _a.head({}).getTypeclass()->Ordinal->ord()(_a.head({}))(_b.head({}));
    return order != ORD::EQ ? order : ord()(_a.rest())(_b.rest());
}



inline VStar IList::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	// Resolve Variables
	ListV l_a = f_a.ResolveToUnsafe<ListV>();

    // Empty is empty
    if (l_a.isEmpty().get()) return ListV();

    // map and recurse
	ArrV g = f.ResolveToUnsafe<ArrV>();
    return ListV(g(l_a._head), fmap()(f)(l_a.rest()));
}


inline VStar IList::Applicative::_pure(const VStar& value) const {
    return ListV(value, ListV());
}	

inline VStar IList::Applicative::_apply(const VStar& boxedFunc, const VStar& app) const {
	ListV m_a = boxedFunc.ResolveToUnsafe<ListV>();
	ListV _app = _app.ResolveToUnsafe<ListV>();

    // empty is no op
	if (m_a.isEmpty().get() || _app.isEmpty().get()) return m_a;

    // else apply every function to first element, then second, etc. and join
    return boxedFunc.getTypeclass()->Semigroup->mappend()
        (fmap()(m_a._head)(app))    // apply over list
        (apply()(m_a.rest())(app)); // apply rest of functiosn over list
}

inline  VStar IList::Monad::_bind(const VStar& m_a, const VStar& a_to_mb) const {
	ListV _ma = m_a.ResolveToUnsafe<ListV>();

	if (_ma.isEmpty().get()) return _ma;

	ArrV arr = a_to_mb.ResolveToUnsafe<ArrV>();

    // map head to list, then append with maps of rest of list
    return boxedFunc.getTypeclass()->Semigroup->mappend()
        (arr(m_a._head))    // map head to list
        (bind()(m_a.rest())(a_to_mb)); // pipe rest of values into function
}

inline VStar IList::Foldable::_foldr(const VStar& f, const VStar& initial, const VStar& foldable) const {
    ListV _ma = foldable.ResolveToUnsafe<ListV>();

    // left is initial
    if (_ma.isEmpty()) return initial;

    // right is apply transformation
	ArrV g = f.ResolveToUnsafe<ArrV>();

    // a 'g' b 'g' c 'g' initial
    return g(_ma._head)(foldr()(f)(initial)(_ma.rest()));
}

inline VStar IList::Traversable::_traverse( const Typeclass* applic, const VStar& f, const VStar& foldable) const {
    ListV _ma = foldable.ResolveToUnsafe<ListV>();

	ArrV g = f.ResolveToUnsafe<ArrV>();

    ArrV cons_f = curry([](const VStar& x, const VStar& ys) {
        return applic->Applicative->liftA2()(cons)(g(x))(ys);
    });
    
    return foldr()(cons_f)(applic->Applicative->pure()(ListV()))(_ma);
}


inline VStar IList::Semigroup::_mappend( const VStar& left, const VStar& right) const {
    ListV _ma = left.ResolveToUnsafe<ListV>();

    // nothing in left, return right
    if (_ma.isEmpty()) return right;

    // else cons recursively
    return cons(_ma._head)(mappend()(_ma.rest())(right));
}

inline VStar IList::Monoid::_mempty() const {
    return ListV();
}