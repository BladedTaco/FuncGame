#pragma once

//// Functor Instance Macro
#define FOLDABLE(INST)		 \
PP__DIRECTIVE(Typeclass, Foldable, INST)



#define IFOLDABLE() 																					PP__NEWLINE \
class Foldable : public virtual IFoldable {																PP__NEWLINE \
private:																								PP__NEWLINE \
	virtual VStar _foldr(const VStar& f, const VStar& initial, const VStar& foldable) const override;	PP__NEWLINE \
public:																									PP__NEWLINE \
	Foldable() = default;																				PP__NEWLINE \
}; 																										PP__NEWLINE \
inline static const Foldable FoldableInst = {};

#include "Foldable_gen.h"