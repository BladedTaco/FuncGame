#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Typeclass/Monoid_gen.h"

#include "Types/Unpack.h"

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


// Functor Interface
class IFoldable {
	// foldr :: (a -> b -> b) -> b -> t a -> b
	TypeclassVirtual(VStar, foldr, f, initial, foldable) = 0;

	// foldMap :: Monoid m => (a -> m) -> t a -> m = 0
	TypeclassVirtual(VStar, foldMap, f, t_a) {
		// const IMonoid* const monoid;
		// get function output monoid 

		// foldr ( mappend . f) mempty
		// foldr()(monoid->mappend()())()
		return {};
	}
	// foldl :: (b -> a -> b) -> b -> t a -> b
	TypeclassVirtual(VStar, foldl, f, initial, foldable) {
		// foldl f a bs = foldr (\b g x -> g (f x b)) id bs a
		return {};
	}
	// foldr1 :: (a -> a -> a) -> t a -> a
	// foldl1 :: (a -> a -> a) -> t a -> a
	// elem :: Eq a => a -> t a -> Bool 
	TypeclassVirtual(Bool, elem, test, foldable) {
		// any . (==);
		return false;
	}
	// maximum :: forall a. Ord a => t a -> a
	TypeclassVirtual(VStar, maximum, foldable) {
		return {};
	}
	// minimum :: forall a. Ord a => t a -> a
	TypeclassVirtual(VStar, minimum, foldable) {
		return {};
	}
	// sum :: Num a => t a -> a
	TypeclassVirtual(VStar, sum, foldable) {
		return {};
	}
	// product :: Num a => t a -> a
	TypeclassVirtual(VStar, product, foldable) {
		return {};
	}
};



