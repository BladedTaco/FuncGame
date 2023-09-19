#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

//// Functor Instance Macro
#define FOLDABLE(INST)		 \
PP__DIRECTIVE(Typeclass, Foldable, INST)

// Functor Interface
class IFoldable {
	// foldMap :: Monoid m => (a -> m) -> t a -> m = 0
	// foldr :: (a -> b -> b) -> b -> t a -> b
	// foldl :: (b -> a -> b) -> b -> t a -> b
	// foldr1 :: (a -> a -> a) -> t a -> a
	// foldl1 :: (a -> a -> a) -> t a -> a
	// elem :: Eq a => a -> t a -> Bool 
	// maximum :: forall a. Ord a => t a -> a
	// minimum :: forall a. Ord a => t a -> a
	// sum :: Num a => t a -> a
	// product :: Num a => t a -> a
};



