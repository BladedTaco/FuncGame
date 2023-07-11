#pragma once

#include "Types/Functor.h"

#include "Types/FDecl.h"



template <typename A>
class IMaybe : public virtual ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const override {
		return &IMaybe<A>::Instances;
	}
public:
	class Functor : public virtual IFunctor {
	private:
		virtual VStar _fmap(const VStar& f, const VStar& f_a) const override {
			// Resolve Variables
			ArrV g = f.ResolveToUnsafe<ArrV>();
			MaybeV m_a = f_a.ResolveToUnsafe<MaybeV>();

			// Logic
			if (m_a._isNothing) {
				return VStar(MaybeV::Nothing(f_a));
			} else {
				return VStar(MaybeV::Just(g(m_a._value).ResolveToUnsafe<int>()));
			}												
		}
	public:
		Functor() = default;
	}; 

	inline static const Functor FunctorInst = {};

public:
	InlineStaticConstStruct(Typeclass, Instances,
		$.Functor = &IMaybe<A>::FunctorInst;
	);
};




// Functor Maybe
template <typename A>
class Maybe : public virtual IMaybe<A> {
private:
	bool _isNothing;
	A _value;
	Maybe() {
		_isNothing = true;
		_value = false;
	}
	Maybe(A a) {
		_isNothing = false;
		_value = a;
	}
	friend IMaybe<A>::Functor;
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
			return _value;
		}
	}

	// Cast Construction
	Maybe(const MaybeV* other);
};


// Functor Maybe
template <>
class Maybe<VStar> : public virtual ITypeclass {
private:

	const Typeclass* Instances;

	virtual const Typeclass* _GetTypeclass() const override {
		return Instances;
	}


	friend VStar;
	friend Maybe;
	
	template <typename A>
	friend class IMaybe<A>::Functor;

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

	
	template <typename A>
	static MaybeV New(A a) {
		MaybeV inst = MaybeV::Maybe(VStar(a));
		inst.SetTypeclass<A>();
		return inst;
	}

	template <>
	static MaybeV New(VStar a) {
		MaybeV inst = MaybeV::Maybe();
		inst.Instances = a.getTypeclass();
		return inst;
	}

	template <typename A>
	static MaybeV New() {
		MaybeV inst = MaybeV::Maybe();
		inst.SetTypeclass<A>();
		inst._value = VStar::New<A>();
		return inst;
	}



	friend class ::Functor<MaybeV>;
public:
	template <typename T>
	void SetTypeclass() {
		Instances = &IMaybe<T>::Instances;
	}

	virtual ~Maybe() = default;

	template <typename A>
	static MaybeV Just(A a) {
		return New(a);
	}

	template <typename A>
	static MaybeV Just(VStar a) {
		return New(a.ResolveToUnsafe<A>());
	}

	template <typename A>
	static MaybeV Nothing() {
		return MaybeV::New<A>();
	}

	static MaybeV Nothing(VStar from) {
		return New(from);
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
};

template <typename A>
Maybe<A>::Maybe(const MaybeV* other) {
	_isNothing = other->_isNothing;
	if (!_isNothing) {
		_value = other->_value.ResolveToUnsafe<A>();
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
			return Maybe<B>::Just(func(f_a._value));    PP__NEWLINE
		}												PP__NEWLINE
	}), 
	()
);
