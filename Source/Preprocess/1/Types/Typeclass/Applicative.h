#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"




#ifndef PP__PREPROCESSING

#include "Types/Typeclass/Functor_gen.h"

#else

include "Types/Typeclass/Functor_gen.h"

#endif


//
//
;

// Applicative Interface
class IApplicative : public virtual IFunctor {
	// pure :: a -> f a
	TypeclassVirtual(VStar, pure, value) = 0;
	// <*> :: f (a -> b) -> f a -> f b
	TypeclassVirtual(VStar, apply, boxedFunc, app) = 0; // return liftA2 id
	// liftA2 :: (a -> b -> c) -> f a -> f b -> f c
	TypeclassVirtual(VStar, liftA2, ternary, boxA, boxB) {
		//(<*>) (fmap f x)

		// Fmap over first box
		VStar f_b = fmap()(ternary)(boxA);

		// Apply curried function from first box to second box
		return apply()(f_b)(boxB);
	};

	// (<*) :: f a -> f b -> f a
	TypeclassVirtual(VStar, leftApply, discard, keep) {
		// (<*) = liftA2 const

		return liftA2()(PreludeV::constant)(discard)(keep);
	};
	// (*>) :: f a -> f b -> f b 
	TypeclassVirtual(VStar, rightApply, keep, discard) {
    	//a1 *> a2 = (id <$ a1) <*> a2

		VStar f_a = map_replace_by()(PreludeV::id)(discard);
		return apply()(f_a)(keep);
	}
}

