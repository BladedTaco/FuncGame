﻿// ---------------------------------------------------------------------------------------
// This File (Func_gen.h) is automatically generated by Preprocess.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once
#include "F:\\Unreal Projects\\HonoursProj 4.27/Source/HonoursProj\\Types/Functor.h"

 /*Added Typeclass Functor Instance Func*/ 
 template <class A , class From> 
 class Functor<Func <A , From> > : public BaseFunctor<Func,A, From> { 
 private: 
 template <class B> 
 inline static auto _fmap = [](Arr<A, B> func, Arr<From, A> f_a) -> Arr<From, B> { 
 return { [=](const From& a) { 
 return func(f_a(a)); 
 } }; }; 
 public: 
 template <class B> 
 inline static auto fmap = curry(_fmap<B>); 
 };
;
