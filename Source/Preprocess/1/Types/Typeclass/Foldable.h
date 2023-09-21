#pragma once

#include "MacroUtils.h"

#include "Functional/Prelude.h"
#include "Functional/Typeclass.h"

#include "Types/Unpack.h"

#ifndef PP__PREPROCESSING

#include "Types/Typeclass/Monoid_gen.h"

#else

include "Types/Typeclass/Monoid_gen.h"

#endif


// Functor Interface
class IFoldable {
	// foldr :: (a -> b -> b) -> b -> t a -> b
	TypeclassVirtual(VStar, foldr, f, initial, foldable) = 0;

	// // foldMap :: Monoid m => (a -> m) -> t a -> m = 0
	// TypeclassVirtual(VStar, foldMap, f, t_a) {
	// 	// const IMonoid* const monoid;
	// 	// get function output monoid 

	// 	// foldr ( mappend . f) mempty
	// 	// foldr()(monoid->mappend()())()
	// 	return {};
	// }
	// // foldl :: (b -> a -> b) -> b -> t a -> b
	// TypeclassVirtual(VStar, foldl, f, initial, foldable) {
	// 	// foldl f a bs = foldr (\b g x -> g (f x b)) id bs a
	// 	return {};
	// }
	// // foldr1 :: (a -> a -> a) -> t a -> a
	// // foldl1 :: (a -> a -> a) -> t a -> a
	// // elem :: Eq a => a -> t a -> Bool 
	// TypeclassVirtual(Bool, elem, test, foldable) {
	// 	// any . (==);
	// 	return false;
	// }
	// // maximum :: forall a. Ord a => t a -> a
	// TypeclassVirtual(VStar, maximum, foldable) {
	// 	return {};
	// }
	// // minimum :: forall a. Ord a => t a -> a
	// TypeclassVirtual(VStar, minimum, foldable) {
	// 	return {};
	// }
	// // sum :: Num a => t a -> a
	// TypeclassVirtual(VStar, sum, foldable) {
	// 	return {};
	// }
	// // product :: Num a => t a -> a
	// TypeclassVirtual(VStar, product, foldable) {
	// 	return {};
	// }
};



