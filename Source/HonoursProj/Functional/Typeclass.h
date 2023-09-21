#pragma once

#include "Preprocess/Include.h"


// Templating
#define _TEMPLATE_LOOP(A) , class A
#define OPT_TEMPLATE(...) NULLARY( (template <MAP_LIST(_TEMPLATE_LOOP, __VA_ARGS__)> PP__NEWLINE), (), __VA_ARGS__)
#define TEMPLATE(...) NULLARY( (template <MAP_LIST(_TEMPLATE_LOOP, __VA_ARGS__)>), (template <>), __VA_ARGS__) PP__NEWLINE
#define STRICT_TEMPLATE(...) template <NULLARY((MAP_LIST(_TEMPLATE_LOOP, __VA_ARGS__)), (class = void*), __VA_ARGS__)> PP__NEWLINE

#define _LIST_LOOP(A) , A
#define TEMPLATE_INST(...) NULLARY( (<MAP_LIST(_LIST_LOOP, __VA_ARGS__)>), (), __VA_ARGS__)

// Defining Function Implementation and their Curried Versions
#define FUNC_DEFN(TEMPLATES, FUNCNAME, DEFN) \
STRICT_TEMPLATE(UNBRACKET TEMPLATES)		 \
inline static auto FUNCNAME = UNBRACKET DEFN; 

#define CURRY_DEFN(TEMPLATES, FUNCNAME) FUNC_DEFN(TEMPLATES, FUNCNAME, (curry(_##FUNCNAME<MAP_LIST(_LIST_LOOP, UNBRACKET TEMPLATES)>)))

// Defining both a Function Implementation and Definition
#define TYPECLASS_FUNC(TEMPLATES, FUNCNAME, DEFN)	PP__NEWLINE \
private:											PP__NEWLINE \
	FUNC_DEFN(TEMPLATES, _## FUNCNAME, DEFN)		PP__NEWLINE \
public:												PP__NEWLINE \
	CURRY_DEFN(TEMPLATES, FUNCNAME)					PP__NEWLINE

// Defining an Optional Typeclass Function
#define TYPECLASS_OPT_FUNC(TEMPLATES, FUNCNAME, DEFN) NULLARY((TYPECLASS_FUNC(TEMPLATES, FUNCNAME, DEFN)), (), UNBRACKET DEFN)

// Defining a Typeclass Template
#define TYPECLASS_WRAP_DEFN(CLS, TEMPLATES, INSTANCE) class CLS<INSTANCE TEMPLATE_INST(UNBRACKET TEMPLATES)> : public Base##CLS<INSTANCE,UNBRACKET TEMPLATES>

#define TYPECLASS_STATIC_DEFN(CLS, TEMPLATES, INSTANCE) class CLS<INSTANCE> : public Base##CLS<INSTANCE>

#define TYPECLASS_DEFN(CLS, TEMPLATES, INSTANCE) NULLARY((TYPECLASS_WRAP_DEFN),(TYPECLASS_STATIC_DEFN), UNBRACKET TEMPLATES)(CLS, TEMPLATES, INSTANCE)
#define STATIC_TYPECLASS_DEFN(CLS, TEMPLATES, INSTANCE) TYPECLASS_STATIC_DEFN(CLS, (), INSTANCE TEMPLATE_INST(UNBRACKET TEMPLATES))

#define TYPECLASS_FUNC_VPTR_LOOP(TYPE, NAME) (*(UNBRACKET TYPE*)NAME)

#define AS_VOIDSTAR(A, B) , void* B


// TYPECLASS_FUNC_VPTR((TEMPLATES...), NAME, (PARAM_TYPE, PARAM_NAME)...)
#define TYPECLASS_FUNC_VPTR(TEMPLATES, NAME, ...)									\
FUNC_DEFN(TEMPLATES, v_##NAME, (													\
	curry([](MAP_BLIST(AS_VOIDSTAR, __VA_ARGS__)) -> decltype(auto) {				\
	return NAME<UNBRACKET TEMPLATES>LOOP(TYPECLASS_FUNC_VPTR_LOOP, __VA_ARGS__);	\
	})																				\
))
//
//TYPECLASS_FUNC_VPTR((B), fmap, ((Arr<A, B>), f), ((F<A, Rest...>), fa))
//
//template <class B> 
//inline static auto v_fmap = curry([](Arr<A, B> f, F<A, Rest...> fa) -> decltype(auto) {
//	return fmap<B>(*(Arr<A, B>*)f) (*(F<A, Rest...>*)fa); 
//});
//
//// Functor Base Instance
//template <template <class, class...> class F, typename A, typename... Rest>
//class BaseFunctor {
//protected:
//	template <class B>
//	inline static Function<F<B, Rest...>, Arr<A, B>, F<A, Rest...>> _fmap;
//
//	template <class B>
//	inline static auto _map_replace_by = [](A a, F<B, Rest...> f_b) -> F<A, Rest...> {
//		Arr<B, A> f = { Prelude::constant<A, B>(a) };
//		return Functor<F<B, Rest...>>::fmap<A>(f)(f_b);
//	};
//public:
//	template <class B>
//	inline static auto fmap = curry(_fmap<B>);
//	template <class B>
//	inline static auto map_replace_by = curry(_map_replace_by<B>);
//
//
//	template <class B>
//	inline static auto v_fmap = curry([](void* func, void* f_a) -> F<B, Rest...> {
//		return fmap<B>(*(Arr<A, B>*)func)(*(F<A, Rest...>*)f_a);
//	});

// Defining a Typeclass Template Signature
//#define TYPECLASS_DEFN_FUNC(TEMPLATES, SIGNATURE, NAME)


#define CurryReturn_Replace(N) const VStar&
#define CurryReturn_Open(N) Arr<CurryReturn_Replace(N),
#define CurryReturn_Close(N) > 

/// CurryReturn(ReturnType, arguments...)
#define CurryReturn(RETURN, ...) \
NULLARY((LOOP3(CurryReturn_Open, BRACKET_LIST2(__VA_ARGS__))), (Arr<void,), __VA_ARGS__) \
RETURN \
NULLARY((LOOP3(CurryReturn_Close, BRACKET_LIST2(__VA_ARGS__))), (>), __VA_ARGS__)

////// TYPECLASS INTERFACING

// Turns Argument Name into VStar Parameter
#define AS_VSTAR(A) , const VStar& A



// TypeclassVirtual_Inner(Return Type, Name, ((VStar ArgName)...), (Argname...) ) { implementation }
#define TypeclassVirtual_Inner(RETURN, NAME, PARAMS, ARGS)	\
public:		\
const CurryReturn(RETURN, UNBRACKET PARAMS) \
NAME() const { return curry([this]PARAMS -> RETURN { return this->_##NAME ARGS; }); };	\
private:	\
virtual RETURN _##NAME PARAMS const

// TypeclassVirtual(Return Type, Name, ArgName...) { implementation }
#define TypeclassVirtual(RETURN, NAME, ...) \
TypeclassVirtual_Inner(RETURN, NAME, ( MAP_LIST(AS_VSTAR, __VA_ARGS__) ), (  __VA_ARGS__ ))

// #define TypeclassVirtualT1_Loop(T1, ...)
// #define TypeclassVirtualT1(RETURN, NAME, T1, ...) \
// TypeclassVirtual_Inner(RETURN, NAME, \
//  ( const Typeclass* T1 LOOP(AS_VSTAR, BRACKET_LIST(__VA_ARGS__)) ),\
//   ( T1, ## __VA_ARGS__ )\
// )


// TypeclassVirtual(Return Type, Name, ArgName...) { implementation }
#define TypeclassVirtualOverride(RETURN, NAME, ...) \
private:                                            \
	virtual RETURN _##NAME ( MAP_LIST(AS_VSTAR, __VA_ARGS__) ) const override

#define TypeclassInst(DATATYPE, TYPECLASS) $.TYPECLASS = &I##DATATYPE::TYPECLASS##Inst
#define TypeclassInstAs(DATATYPE, TYPECLASS, AS) $.AS = &I##DATATYPE::TYPECLASS##Inst







// TypeclassVirtual_Inner(Return Type, Name, ((VStar ArgName)...), (Argname...) ) { implementation }
#define TypeclassVirtualDecl_Inner(RETURN, NAME, PARAMS, ARGS)	\
public:		\
const CurryReturn(RETURN, UNBRACKET PARAMS) \
NAME() const;	\
private:	\
virtual RETURN _##NAME PARAMS const

// TypeclassVirtual_Inner(Return Type, Name, ((VStar ArgName)...), (Argname...) ) { implementation }
#define TypeclassVirtualImpl_Inner(CLS, RETURN, NAME, PARAMS, ARGS)	\
const CurryReturn(RETURN, UNBRACKET PARAMS) \
CLS::NAME() const { return curry([this]PARAMS->RETURN{ return this->_##NAME ARGS; }); };	\
RETURN CLS::_##NAME PARAMS const

// TypeclassVirtual_Inner(Return Type, Name, ((VStar ArgName)...), (Argname...) ) { implementation }
#define TypeclassVirtualImplPure_Inner(CLS, RETURN, NAME, PARAMS, ARGS)	\
const CurryReturn(RETURN, UNBRACKET PARAMS) \
CLS::NAME() const { return curry([this]PARAMS->RETURN{ return this->_##NAME ARGS; }); }




// TypeclassVirtual(Return Type, Name, ArgName...) { implementation }
#define TypeclassVirtualDecl(RETURN, NAME, ...)\
TypeclassVirtualDecl_Inner(RETURN, NAME, ( MAP_LIST(AS_VSTAR, __VA_ARGS__) ), (  __VA_ARGS__ ))

// TypeclassVirtual(Return Type, Name, ArgName...) { implementation }
#define TypeclassVirtualImpl(CLS, RETURN, NAME, ...)\
TypeclassVirtualImpl_Inner(CLS, RETURN, NAME, ( MAP_LIST(AS_VSTAR, __VA_ARGS__) ), (  __VA_ARGS__ ))

// TypeclassVirtual(Return Type, Name, ArgName...) { implementation }
#define TypeclassVirtualImplPure(CLS, RETURN, NAME, ...)\
TypeclassVirtualImplPure_Inner(CLS, RETURN, NAME, ( MAP_LIST(AS_VSTAR, __VA_ARGS__) ), (  __VA_ARGS__ ))

//
//
//// TypeclassVirtual_Inner(Return Type, Name, ((VStar ArgName)...), (Argname...) ) { implementation }
//#define TypeclassVirtualTemplated_Inner(TEMPS, RETURN, NAME, PARAMS, ARGS)	\
//public:		\
//template <typename TEMPS>	\
//const auto NAME(TEMPS) const { return curry([this]PARAMS{ return this->_##NAME<TEMPS> ARGS; }); };	\
//private:	\
//template <typename TEMPS>	\
//virtual RETURN _##NAME PARAMS const
//
//// TypeclassVirtual(Return Type, Name, ArgName...) { implementation }
//#define TypeclassVirtualTemplated(TEMP, RETURN, NAME, ...) \
//TypeclassVirtualTemplated_Inner(TEMP, RETURN, NAME, ( MAP_LIST(AS_VSTAR, __VA_ARGS__) ), (  __VA_ARGS__ ))
//
//
//class Q {
//public:		
//	const auto q(class Typeclass* tc) const { return curry([this](){ return this->_q(); }); };	
//private:	
//	virtual int _q() const {
//		
//	}
//
//};

//#pragma warning(push)
#pragma warning(disable: 4250)
//warning disabled due to it causing an error despite being information
//#pragma warning(pop)