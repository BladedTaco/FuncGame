// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "LoopMacros.h"


#define EXPAND(x) x
#define UNBRACKET(...) __VA_ARGS__
#define BRACKET(x) LBRACKET x RBRACKET
#define DEFER(FUNC, ...) FUNC(__VA_ARGS__)


#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__


#define NUM_ARGS(...)  NUM_ARGS_ ( IGNORE_FIRST ( , ##__VA_ARGS__ , __NATURAL_64_INTS() ) ) 
#define NUM_ARGS_(...) EXPAND(__NATURAL_64_ARGS(__VA_ARGS__))

#define NO_ARGS(...)  NUM_ARGS_ ( IGNORE_FIRST ( , ##__VA_ARGS__ , __NATURAL_64_GT0() ) ) 


#define __NATURAL_64_ARGS( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define __NATURAL_64_INTS()  63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define __NATURAL_64_GT0()  1,1,1,1, \
         1,1,1,1,1,1,1,1,1,1, \
         1,1,1,1,1,1,1,1,1,1, \
         1,1,1,1,1,1,1,1,1,1, \
         1,1,1,1,1,1,1,1,1,1, \
         1,1,1,1,1,1,1,1,1,1, \
         1,1,1,1,1,1,1,1,1,0


#define LBRACKET (
#define RBRACKET )

#define IGNORE_FIRST(_, ...) __VA_ARGS__
#define TO_FIRST (FIRST, ...) FIRST

#define APPLY(DO, VARS) DO VARS
#define APPLY1(DO, VARS) DO VARS
#define APPLY2(DO, VARS) DO VARS
#define APPLY3(DO, VARS) DO VARS
#define APPLY4(DO, VARS) DO VARS
#define APPLY5(DO, VARS) DO VARS
#define APPLY6(DO, VARS) DO VARS
#define APPLY7(DO, VARS) DO VARS
#define APPLY8(DO, VARS) DO VARS
#define APPLY9(DO, VARS) DO VARS
#define APPLY0(DO, VARS) DO VARS

#define STRIP_FIRST(X) APPLY1(IGNORE_FIRST, (X))


// LOOP VARIATION MACROS
#define BZIP_BASE(VAR, VARS) , LBRACKET VAR, VARS RBRACKET
#define ZIP_BASE(VAR, VARS) , LBRACKET VAR, UNBRACKET VARS RBRACKET
#define MZIP_BASE(VAR, VARS) , LBRACKET UNBRACKET VAR, UNBRACKET VARS RBRACKET

#define BZIP_BASE2(VAR, VARS) , LBRACKET VAR, VARS RBRACKET
#define ZIP_BASE2(VAR, VARS) , LBRACKET VAR, UNBRACKET VARS RBRACKET
#define MZIP_BASE2(VAR, VARS) , LBRACKET UNBRACKET VAR, UNBRACKET VARS RBRACKET

#define BZIP_BASE3(VAR, VARS) , LBRACKET VAR, VARS RBRACKET
#define ZIP_BASE3(VAR, VARS) , LBRACKET VAR, UNBRACKET VARS RBRACKET
#define MZIP_BASE3(VAR, VARS) , LBRACKET UNBRACKET VAR, UNBRACKET VARS RBRACKET


#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
#define VA_SELECT( NAME, ... ) EXPAND(SELECT( NAME, NUM_ARGS(__VA_ARGS__) )(__VA_ARGS__))

#define LOOP_N3(BASE, N, DO, ...) EXPAND(SELECT(LOOP, N)(BASE, DO, __VA_ARGS__))
#define LOOP_N2(BASE, N, DO, ...) LOOP_N3(BASE, N, DO, __VA_ARGS__)

#define LOOP_I(BASE, DO, ...) LOOP_N2(BASE, NUM_ARGS(__VA_ARGS__), DO, __VA_ARGS__)
#define LOOP(DO, ...) LOOP_I(APPLY2, DO, __VA_ARGS__)


#define LOOP2_N3(BASE, N, DO, ...) EXPAND(SELECT(LOOP2, N)(BASE, DO, __VA_ARGS__))
#define LOOP2_N2(BASE, N, DO, ...) LOOP2_N3(BASE, N, DO, __VA_ARGS__)

#define LOOP2_I(BASE, DO, ...) LOOP2_N2(BASE, NUM_ARGS(__VA_ARGS__), DO, __VA_ARGS__)
#define LOOP2(DO, ...) LOOP2_I(APPLY6, DO, __VA_ARGS__)

#define LOOP3_N3(BASE, N, DO, ...) EXPAND(SELECT(LOOP3, N)(BASE, DO, __VA_ARGS__))
#define LOOP3_N2(BASE, N, DO, ...) LOOP3_N3(BASE, N, DO, __VA_ARGS__)

#define LOOP3_I(BASE, DO, ...) LOOP3_N2(BASE, NUM_ARGS(__VA_ARGS__), DO, __VA_ARGS__)
#define LOOP3(DO, ...) LOOP3_I(APPLY9, DO, __VA_ARGS__)


#define ZIP(DO, ...) APPLY3(IGNORE_FIRST, (LOOP_I(ZIP_BASE, DO, __VA_ARGS__)))
#define BZIP(DO, ...) APPLY3(IGNORE_FIRST, (LOOP_I(BZIP_BASE, DO, __VA_ARGS__)))
#define MZIP(DO, ...) APPLY3(IGNORE_FIRST, (LOOP_I(MZIP_BASE, DO, __VA_ARGS__)))

#define ZIP2(DO, ...) APPLY6(IGNORE_FIRST, (LOOP2_I(ZIP_BASE2, DO, __VA_ARGS__)))
#define BZIP2(DO, ...) APPLY6(IGNORE_FIRST, (LOOP2_I(BZIP_BASE2, DO, __VA_ARGS__)))
#define MZIP2(DO, ...) APPLY6(IGNORE_FIRST, (LOOP2_I(MZIP_BASE2, DO, __VA_ARGS__)))


#define ZIP3(DO, ...) APPLY7(IGNORE_FIRST, (LOOP3_I(ZIP_BASE3, DO, __VA_ARGS__)))
#define BZIP3(DO, ...) APPLY7(IGNORE_FIRST, (LOOP3_I(BZIP_BASE3, DO, __VA_ARGS__)))
#define MZIP3(DO, ...) APPLY7(IGNORE_FIRST, (LOOP3_I(MZIP_BASE3, DO, __VA_ARGS__)))



#define TAKE_BASE(_, VAR, ...) , LBRACKET VAR RBRACKET
#define TAKE_N(N, ...) APPLY4(IGNORE_FIRST, (LOOP_##N(TAKE_BASE, BRACKET, __VA_ARGS__)))

#define APP(DO, VAR) DO(VAR)

#define BRACKET_LIST(...) APPLY4(IGNORE_FIRST, (LOOP_I(TAKE_BASE, BRACKET, __VA_ARGS__)))
#define BRACKET_LIST2(...) APPLY8(IGNORE_FIRST, (LOOP2_I(TAKE_BASE, BRACKET, __VA_ARGS__)))

#define SEMICOLON(X) X;
#define LIST_TO_LINES(...) LOOP(SEMICOLON, BRACKET_LIST(__VA_ARGS__))

#define _LIST_LOOP(A) , A
#define MAP_LIST(LOOPER, ...) STRIP_FIRST(LOOP(LOOPER, BRACKET_LIST(__VA_ARGS__)))
#define MAP_BLIST(LOOPER, ...) STRIP_FIRST(LOOP(LOOPER, __VA_ARGS__))

#define _NULLARY_0(ARGSFUL, ARGLESS) ARGLESS
#define _NULLARY_1(ARGSFUL, ARGLESS) ARGSFUL

#define NULLARY(ARGSFUL, ARGLESS, ...) APPLY5(UNBRACKET,  SELECT(_NULLARY, NO_ARGS(__VA_ARGS__) )(ARGSFUL, ARGLESS))

#define _OPTIONAL_0(ARGSFUL)
#define _OPTIONAL_1(ARGSFUL) ARGSFUL
#define OPTIONAL(ARGSFUL, ...) SELECT(_OPTIONAL, NUM_ARGS_ ( IGNORE_FIRST ( , ##__VA_ARGS__ , __NATURAL_64_GT0() ) ) )(ARGSFUL)






// START OF NEW PROJECT MACROS

// Looper macros for struct definition and struct constructor defaults
//#define _LOAD_ASSETS_IMPL(TYPE, NAME, LOCATION) , NAME(TEXT(LOCATION))

#define _LOAD_ASSETS_DEF(TYPE, NAME, LOCATION) TYPE* NAME;
#define _LOAD_ASSETS_IMPL(TYPE, NAME, ASSET) , NAME(ASSET.Get())

//// LOAD ASSETS ( (TYPE, NAME, LOCATION), ...) 
//#define LOAD_ASSETS(...)                                \
//struct FConstructorStatics {                            \
//    LOOP(_LOAD_ASSETS_DEF, __VA_ARGS__)                 \
//    FConstructorStatics() :                             \
//    STRIP_FIRST(LOOP(_LOAD_ASSETS_IMPL, __VA_ARGS__))   \
//    {}                                                  \
//};                                                      \
//static FConstructorStatics

// LOAD ASSETS ( (TYPE, NAME, ASSET), ...) 
//#define LOAD_ASSETS(...)                                \
//struct FConstructorStatics {                            \
//    LOOP(_LOAD_ASSETS_DEF, __VA_ARGS__)                 \
//    FConstructorStatics() :                             \
//    STRIP_FIRST(LOOP(_LOAD_ASSETS_IMPL, __VA_ARGS__))   \
//    {}                                                  \
//};                                                      \
//static FConstructorStatics
//
