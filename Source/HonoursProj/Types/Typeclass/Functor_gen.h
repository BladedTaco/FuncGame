﻿// ---------------------------------------------------------------------------------------
// This File (Functor_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "MacroUtils.h"
#include "Functional\Prelude.h"
#include "Functional\Typeclass.h"
#include "Types\Unpack.h"
class IFunctor {
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > fmap() const { return curry([this]( const VStar& f , const VStar& f_a ) -> VStar { return this->_fmap ( f, f_a ); }); }; private: virtual VStar _fmap ( const VStar& f , const VStar& f_a ) const = 0;
	public: const Arr<const VStar&, Arr<const VStar&, VStar > > map_replace_by() const { return curry([this]( const VStar& a , const VStar& f_b ) -> VStar { return this->_map_replace_by ( a, f_b ); }); }; private: virtual VStar _map_replace_by ( const VStar& a , const VStar& f_b ) const { 
		Arr<VStar, VStar> f = { PreludeV::constant(a) };
		return _fmap(f, f_b);
	};
};