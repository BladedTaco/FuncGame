﻿// ---------------------------------------------------------------------------------------
// This File (Bool_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "Types\Show.h"
#include "Types/VStar.h"
class IBool : public virtual ITypeclass {
private:
	virtual const TSharedPtr<Typeclass> _GetTypeclass() const override {
		return NoopPtr(&IBool::Instances);
	}
public:
	class Show : public virtual IShow {
	private:
		virtual FString _show(const VStar& me) const override;
	public:
		Show() = default;
	};
	inline static const Show ShowInst = {};
public:
	static const inline Typeclass Instances = []{ Typeclass ${}; $.Show = &IBool::ShowInst;; return $; }()
;
};
class Bool : public virtual IBool {
private:
	bool _value;
	friend IBool;
public:
	virtual ~Bool() = default;
	Bool(bool value) : _value(value) {};
	Bool(const Bool& other) : _value(other._value) {};
	virtual bool get() const { return _value; }
};
inline FString IBool::Show::_show(const VStar& me) const {
	bool a = me.ResolveToUnsafe<Bool>().get();
	return a ? FString(TEXT("✓")) : FString(TEXT("X"));
}
