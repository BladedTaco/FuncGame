#pragma once

#include "Types/Functor.h"
#include "Types/Show.h"

#include "Types/FDecl.h"


#ifndef PP__PREPROCESSING

#include "Misc/Optional.h"

#else

include "Misc/Optional.h"

#endif



class IMaybe : public virtual ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const override {
		return &IMaybe::Instances;
	}
public:
	class Functor : public virtual IFunctor {
	private:
		virtual VStar _fmap(const VStar& f, const VStar& f_a) const override;
	public:
		Functor() = default;
	}; 

	inline static const Functor FunctorInst = {};

	class Show : public virtual IShow {
	private:
		virtual FString _show(const VStar& a) const override;
	public:
		Show() = default;
	};
	inline static const Show ShowInst = {};

public:
	InlineStaticConstStruct(Typeclass, Instances,
		$.Functor = &IMaybe::FunctorInst;
		$.Show = &IMaybe::ShowInst;
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
	friend class ::Functor<Maybe<A>>;
	friend MaybeV;
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

	friend IMaybe::Functor;
	friend IMaybe::Show;

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
		return MaybeV::Maybe(VStar(a));
	}
	template <>
	static MaybeV Just(VStar a) {
		return MaybeV::Maybe(a);
	}

	static MaybeV Nothing() {
		return MaybeV::Maybe();
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



inline VStar IMaybe::Functor::_fmap(const VStar& f, const VStar& f_a) const {
	// Resolve Variables
	ArrV g = f.ResolveToUnsafe<ArrV>();
	MaybeV m_a = f_a.ResolveToUnsafe<MaybeV>();

	// Logic
	if (m_a._isNothing) {
		return VStar(MaybeV::Nothing());
	} else {
		//return VStar(MaybeV::Just(g(m_a._value).ResolveToUnsafe<int>()));
		//return VStar(MaybeV::Just(g(m_a._value)));
		VStar result = g(m_a._value);
		return VStar(MaybeV::Just(result));
	}
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






//
//
//// Functor Maybe
//template <typename A>
//class Maybe : public Functor<Maybe<A>> {
//private:
//	bool _isNothing;
//	A _value;
//	Maybe() {
//		_isNothing = true;
//		_value = false;
//	}
//	Maybe(A a) {
//		_isNothing = false;
//		_value = a;
//	}
//	friend class Functor<Maybe<A>>;
//public:
//	static Maybe<A> Just(A a) {
//		return Maybe<A>(a);
//	}
//	static Maybe<A> Nothing() {
//		return Maybe<A>();
//	}
//public:
//	A fromMaybe(A fallback) {
//		if (_isNothing) {
//			return fallback;
//		} else {
//			return _value;
//		}
//	}
//};

//
//template <>
//class Maybe<VStar> {
//private:
//	bool _isNothing;
//	VStar _value;
//	Maybe() {
//		_isNothing = true;
//	}
//	template <typename A>
//	Maybe(A a) {
//		_isNothing = false;
//		_value = VStar(a);
//	}
//	friend class Functor<Maybe<VStar>>;
//public:
//	template <typename A>
//	static Maybe<VStar> Just(A a) {
//		return Maybe(a);
//	}
//	static Maybe<VStar> Nothing() {
//		return Maybe();
//	}
//
//	template <typename OtherInner>
//	Maybe(Maybe<OtherInner>& other) {
//		_isNothing = other._isNothing;
//		_value = VStar(other._value);
//	}
//
//	template <>
//	Maybe(Maybe<VStar>& other) 
//		: _value(other._value)
//		, _isNothing(other._isNothing) {};
//public:
//	template <typename A>
//	A fromMaybe(A fallback) {
//		if (_isNothing) {
//			return fallback;
//		} else {
//			return _value.Get<A>();
//		}
//	}
//};


//
//class IMaybe {
//private:
//	bool _isNothing;
//	VStar _value;
//	IMaybe() {
//		_isNothing = true;
//	}
//	template <typename A>
//	IMaybe(A a) {
//		_isNothing = false;
//		_value = a;
//	}
//	friend class Functor<Maybe<VStar>>;
//public:
//	static Maybe<A> Just(A a) {
//		return Maybe<A>(a);
//	}
//	static Maybe<A> Nothing() {
//		return Maybe<A>();
//	}
//public:
//	A fromMaybe(A fallback) {
//		if (_isNothing) {
//			return fallback;
//		} else {
//			return _value;
//		}
//	}
//
//	Maybe<class VStar> Void() {
//
//	}
//};


template <typename A>
auto fromMaybe = curry([](A a, Maybe<A> m_a) -> A {
	return m_a.fromMaybe(a);
});


FUNCTOR((A), Maybe, (
	[](Arr<A, B> func, Maybe<A> f_a) -> Maybe<B> {		PP__NEWLINE
		if (f_a._isNothing) {						    PP__NEWLINE
			return Maybe<B>::Nothing();				    PP__NEWLINE
		} else {									    PP__NEWLINE
			return Maybe<B>::Just(func(f_a._value.GetValue()));    PP__NEWLINE
		}												PP__NEWLINE
	}), 
	()
);

SHOW((A), Maybe, ());
