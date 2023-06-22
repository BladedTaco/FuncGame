#pragma once



// Templating
#define _TEMPLATE_LOOP(A) , class A
#define OPT_TEMPLATE(...) NULLARY( (template <MAP_LIST(_TEMPLATE_LOOP, __VA_ARGS__)>), (), __VA_ARGS__)
#define TEMPLATE(...) NULLARY( (template <MAP_LIST(_TEMPLATE_LOOP, __VA_ARGS__)>), (template <>), __VA_ARGS__)

#define _LIST_LOOP(A) , A
#define TEMPLATE_INST(...) NULLARY( (<MAP_LIST(_LIST_LOOP, __VA_ARGS__)>), (), __VA_ARGS__)

// Defining Function Implementation and their Curried Versions
#define FUNC_DEFN(TEMPLATES, FUNCNAME, DEFN)	\
OPT_TEMPLATE(UNBRACKET TEMPLATES)					\
inline static auto FUNCNAME = UNBRACKET DEFN;

#define CURRY_DEFN(TEMPLATES, FUNCNAME) FUNC_DEFN(TEMPLATES, FUNCNAME, (curry(_##FUNCNAME TEMPLATE_INST( UNBRACKET TEMPLATES))))

// Defining both a Function Implementation and Definition
#define TYPECLASS_FUNC(TEMPLATES, FUNCNAME, DEFN)	\
private:											\
	FUNC_DEFN(TEMPLATES, _## FUNCNAME, DEFN)		\
public:												\
	CURRY_DEFN(TEMPLATES, FUNCNAME)

// Defining an Optional Typeclass Function
#define TYPECLASS_OPT_FUNC(TEMPLATES, FUNCNAME, DEFN) NULLARY((TYPECLASS_FUNC(TEMPLATES, FUNCNAME, DEFN)), (), UNBRACKET DEFN)

// Defining a Typeclass Template
#define TYPECLASS_WRAP_DEFN(CLS, TEMPLATES, INSTANCE) class CLS<INSTANCE TEMPLATE_INST(UNBRACKET TEMPLATES)> : public Base##CLS<INSTANCE, UNBRACKET TEMPLATES>

#define TYPECLASS_STATIC_DEFN(CLS, TEMPLATES, INSTANCE) class CLS<INSTANCE> : public Base##CLS<INSTANCE>

#define TYPECLASS_DEFN(CLS, TEMPLATES, INSTANCE) NULLARY((TYPECLASS_WRAP_DEFN),(TYPECLASS_STATIC_DEFN), UNBRACKET TEMPLATES)(CLS, TEMPLATES, INSTANCE)

// Defining a Typeclass Template Signature
//#define TYPECLASS_DEFN_FUNC(TEMPLATES, SIGNATURE, NAME)