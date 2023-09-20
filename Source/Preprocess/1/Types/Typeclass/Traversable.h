#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Foldable_gen.h"
#include "Types/Typeclass/Functor_gen.h"

#include "Types/Unpack.h"
#include "Types/FDecl.h"

//// Functor Instance Macro
#define TRAVERSABLE(INST)		 \
PP__DIRECTIVE(Typeclass, Traversable, INST)

#define ITRAVERSABLE() 																PP__NEWLINE \
class Traversable : public virtual ITraversable {									PP__NEWLINE \
private:																			PP__NEWLINE \
	virtual VStar _traverse(const Typeclass* applic, const VStar& f, const VStar& foldable) const override;	PP__NEWLINE \
public:																				PP__NEWLINE \
	Traversable() = default;														PP__NEWLINE \
}; 																					PP__NEWLINE \
inline static const Traversable TraversableInst = {};

// Functor Interface
class ITraversable : public virtual IFoldable, public virtual IFunctor {
	// traverse :: Applicative f => (a -> f b) -> t a -> f (t b) = 0;
	TypeclassVirtualT1(VStar, traverse, applic, f, foldable) = 0;
		// {
		// 	VStar mapped = fmap()(f)(foldable);
		// 	return sequenceA()(mapped);
		// };
	// sequenceA :: Applicative f => t (f a) -> f (t a)
	TypeclassVirtualT1(VStar, sequenceA, applic, foldable) {
		return traverse()(Prelude::id<VStar>)(foldable);
	};
};
