﻿// ---------------------------------------------------------------------------------------
// This File (Foldable_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "MacroUtils.h"
#include "Functional\Prelude.h"
#include "Functional\Typeclass.h"
#include "Types\Unpack.h"
#include "Types/Typeclass/Monoid_gen.h"
class IFoldable {
	public: const Arr<const VStar&, Arr<const VStar&, Arr<const VStar&, VStar > > > foldr() const { return curry([this]( const VStar& f , const VStar& initial , const VStar& foldable ) -> VStar { return this->_foldr ( f, initial, foldable ); }); }; private: virtual VStar _foldr ( const VStar& f , const VStar& initial , const VStar& foldable ) const = 0;
};