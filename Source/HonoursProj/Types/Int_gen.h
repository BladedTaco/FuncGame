﻿// ---------------------------------------------------------------------------------------
// This File (Int_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/Ord.h"
#include "Types/VStar.h"
#include "C:\\Users\\v2tac\\Desktop\\UNI\\Semester 8\\FIT444X - Honours Thesis\\Unreal\\HonoursProj/Source/HonoursProj\\Types/FDecl.h"
class INumber {
public:
	class Ordinal : public virtual IOrdinal {
	private:
		virtual ORD _ord(const VStar& me, const VStar& other) const override;
	public:
		Ordinal() = default;
	};
	inline static const Ordinal POrdinal = {};
public:
	static const inline Typeclass Instances = []{ Typeclass ${}; $.Ordinal = &INumber::POrdinal; return $; }()
;
};
template <typename A>
class Number : public virtual INumber {
private:
	A _value;
	friend class ::Ordinal<Number<A>>;
public:
	virtual ~Number() = default;
	Number(A value) : _value(value) {}
	virtual A get() const { return _value; }
	Number(const NumberV* other);
};
template <>
class Number<VStar> : public virtual INumber {
private:
	friend class VStar;
	VStar _value;
	friend class ::Ordinal<NumberV>;
public:
	virtual ~Number() = default;
	template <typename A>
	Number(A value)
		: _value(value) {};
	template <typename A>
	const A* get() const { return _value.GetUnsafePtr<A>(); }
	template <typename A>
	Number(const Number<A>& other) 
		: _value(other.get()) {}
	template <>
	Number(const NumberV& other)
		: _value(other._value) {};
	Number(const NumberV& other) {
		_value = other._value;
	};
	Number(NumberV&& other) {
		_value = VStar(other);
	}
};

 /*Added Typeclass Ordinal Instance Number*/ 
 template <class A> 
 class Ordinal<Number <A> > : public BaseOrdinal<Number <A> > { 
 private: 
 template <class = auto> 
 inline static auto _ord = [](Number<A> a, Number<A> b) -> ORD { 
 return a._value == b._value ? ORD::EQ : a._value < b._value ? ORD::LT : ORD::GT; 
 }; 
 public: 
 template <class = auto> 
 inline static auto ord = curry(_ord<>); 
 };
;
