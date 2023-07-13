#pragma once

#include "Types/Ord.h"
#include "Types/Show.h"



#ifndef PP__PREPROCESSING

#include "Types/VStar.h"

#else

include "Types/VStar.h"

#endif

#include "Types/FDecl.h"


#define InlineStaticConstStruct(T, NAME, ...) \
static const inline T NAME = []{ T ${}; __VA_ARGS__; return $; }()

//class INumber {
//public:
//	class Ordinal : public virtual IOrdinal {
//	private:
//		virtual ORD _ord(const VStar& me, const VStar& other) const override;
//	public:
//		Ordinal() = default;
//	};
//
//	inline static const Ordinal POrdinal = {};
//
//public:
//	InlineStaticConstStruct(Typeclass, Instances,
//		$.Ordinal = &INumber::POrdinal
//	);
//};



template <typename A>
class INumber : public virtual ITypeclass {
private:
	virtual const Typeclass* _GetTypeclass() const override {
		return &INumber<A>::Instances;
	}
public:
	class Ordinal : public virtual IOrdinal {
	private:
		virtual ORD _ord(const VStar& me, const VStar& other) const override;
	public:
		Ordinal() = default;
	};
	inline static const Ordinal OrdinalInst = {};

	class Show : public virtual IShow {
	private:
		virtual FString _show(const VStar& me) const override;
	public:
		Show() = default;
	};
	inline static const Show ShowInst = {};

public:
	InlineStaticConstStruct(Typeclass, Instances,
		$.Ordinal = &INumber<A>::OrdinalInst;
		$.Show = &INumber<A>::ShowInst;
	);
};





template <typename A>
class Number : public virtual INumber<A> {
private:
	A _value;
	friend NumberV;
	friend class ::Ordinal<Number<A>>;
public:
	virtual ~Number() = default;
	Number(A value) : _value(value) {}
	virtual A get() const { return _value; }

	// Cast Construction
	Number(const NumberV* other);
	//// Cast Construction
	//Number(const NumberV* other) {
	//	_value = other->_value.ResolveTo<A>();
	//}

	//VStar ToVStar() const {
	//	if constexpr (not_template_t<A>) {
	//		return VStar(NumberV(_value));
	//	} else {
	//		return VStar(NumberV(_value.ToVStar()));
	//	}
	//}
};


template <>
class Number<VStar> : public virtual ITypeclass {
private:
	friend VStar;

	friend Number;

	template <typename A>
	friend Number<A>::Number(const NumberV* other);

	VStar _value;
	friend class ::Ordinal<NumberV>;

	const Typeclass* Instances;

	virtual const Typeclass* _GetTypeclass() const override {
		return Instances;
	}

public:
	template <typename T>
	void SetTypeclass() {
		Instances = &INumber<T>::Instances;
	}

	virtual ~Number() = default;
	template <typename A>
	Number(A value)
		: _value(value) {
		SetTypeclass<A>();
	};

	template <typename A>
	const A* get() const { return _value.GetUnsafePtr<A>(); }

	// Copy Construction
	template <typename A>
	Number(const Number<A>& other) 
		: _value(other.get()) {
		SetTypeclass<A>();
	}

	// Copy Constructor for NumberVs
	template <>
	Number(const NumberV& other)
		: _value(other._value) 
		, Instances(other.GetTypeclass()) {};

	Number(const NumberV& other) {
		_value = other._value;
		Instances = other.GetTypeclass();
	};


	// Move Constructor is move into container
	Number(NumberV&& other) {
		_value = VStar(other);
		Instances = other.GetTypeclass();
	}
};


template <typename A>
Number<A>::Number(const NumberV* other) {
	_value = other->_value.ResolveToUnsafe<A>();
}

template <typename A>
inline ORD INumber<A>::Ordinal::_ord(const VStar& me, const VStar& other) const {
	// Resolve
	A a = me.ResolveToUnsafe<Number<A>>().get();
	A b = other.ResolveToUnsafe<Number<A>>().get();

	// Calculate
	return a == b ? ORD::EQ : a < b ? ORD::LT : ORD::GT;
}

template <typename A>
inline FString INumber<A>::Show::_show(const VStar& me) const {
	// Resolve
	A a = me.ResolveToUnsafe<Number<A>>().get();

	// return result
	return FString::Format(TEXT("{0}"), { a });
}

//
//class INumber {
//public:
//	static class Ordinal : public virtual IOrdinal {
//	private:
//		virtual ORD _ord(VStar me, VStar other) const override { return ORD::EQ; }
//	} POrdinal;
//
//};

//class INumber::Ordinal : public virtual IOrdinal {
//private:
//	virtual ORD _ord(VStar me, VStar other) const override { return ORD::EQ; }
//};



ORDINAL((A), Number, (
	[](Number<A> a, Number<A> b) -> ORD {													PP__NEWLINE
		return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT;	PP__NEWLINE
	})
);

SHOW((A), Number, ());

//template <> class Ordinal<IOrdinal> : public BaseOrdinal<IOrdinal> {
//private: 
//	inline static auto _ord = [](IOrdinal& a, IOrdinal& b) -> ORD {
//		return a.ord()(a)(b);
//	};
//public: 
//	inline static auto ord = curry(_ord);
//};





//
//template <>
//class Ordinal<NumberV> : public BaseOrdinal<NumberV> {
//private:
//	template <class _ = void*>
//	inline static auto _ord = [](NumberV* a, NumberV* b) -> ORD {
//		float v0, v1;
//		if (a->_value.ValidCast<int>()) {
//			v0 = *a->get<int>();
//			v1 = *b->get<int>();
//		} else if (a->_value.ValidCast<float>()) {
//			v0 = *a->get<float>();
//			v1 = *b->get<float>();
//		} else { return ORD::EQ; }
//
//		return v0 == v1
//			? ORD::EQ 
//			: v0 < v1
//				? ORD::LT 
//				: ORD::GT;
//	}; 
//public:
//	template <class _ = void*> 
//	inline static auto ord = curry(_ord<>);
//};