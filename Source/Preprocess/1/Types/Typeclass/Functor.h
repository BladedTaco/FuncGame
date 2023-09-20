#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"


// Functor Instance Macro
#define FUNCTOR(INST) PP__DIRECTIVE(Typeclass, Functor, INST)

#define IFUNCTOR() 															PP__NEWLINE \
class Functor : public virtual IFunctor {									PP__NEWLINE \
private:																	PP__NEWLINE \
	virtual VStar _fmap(const VStar& f, const VStar& f_a) const override;	PP__NEWLINE \
public:																		PP__NEWLINE \
	Functor() = default;													PP__NEWLINE \
}; 																			PP__NEWLINE \
inline static const Functor FunctorInst = {};

// // Functor Instance Macro
// #define FUNCTOR(TEMPLATES, INST, FMAP, MAP_REPLACE_BY)		 \
// PP__DIRECTIVE(Typeclass, Functor, INST)						 \
// TEMPLATE(UNBRACKET TEMPLATES)								 \
// TYPECLASS_DEFN(Functor, TEMPLATES, INST) {					 \
// 	TYPECLASS_FUNC((B), fmap, FMAP)							 \
// 	TYPECLASS_OPT_FUNC((B), map_replace_by, MAP_REPLACE_BY)	 \
// };




// Functor Interface
class IFunctor {
	// fmap :: (a -> b) -> f a -> f b
	TypeclassVirtual(VStar,	fmap, f, f_a) = 0;
	// (<$) :: a -> f b -> f a
	TypeclassVirtual(VStar, map_replace_by, a, f_b) { 
		Arr<VStar, VStar> f = { Prelude::constant<VStar, VStar>(a) };
		return _fmap(f, f_b);
	};
};



