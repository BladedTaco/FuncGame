#pragma once


//// Functor Instance Macro
#define TRAVERSABLE(INST)		 \
PP__DIRECTIVE(Typeclass, Traversable, INST)

#define ITRAVERSABLE() 																PP__NEWLINE \
class Traversable : public virtual ITraversable, public virtual Foldable, public virtual Functor { PP__NEWLINE \
private:																			PP__NEWLINE \
	virtual VStar _traverse(const VStar& applic, const VStar& f, const VStar& foldable) const override;	PP__NEWLINE \
public:																				PP__NEWLINE \
	Traversable() = default;														PP__NEWLINE \
}; 																					PP__NEWLINE \
inline static const Traversable TraversableInst = {};

#include "Traversable_gen.h"