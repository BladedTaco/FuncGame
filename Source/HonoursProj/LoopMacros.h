// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// defines loop macros up to 64 iterations
#define LOOP_64(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_63(BASE, DO, __VA_ARGS__))
#define LOOP_63(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_62(BASE, DO, __VA_ARGS__))
#define LOOP_62(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_61(BASE, DO, __VA_ARGS__))
#define LOOP_61(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_60(BASE, DO, __VA_ARGS__))
#define LOOP_60(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_59(BASE, DO, __VA_ARGS__))
#define LOOP_59(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_58(BASE, DO, __VA_ARGS__))
#define LOOP_58(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_57(BASE, DO, __VA_ARGS__))
#define LOOP_57(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_56(BASE, DO, __VA_ARGS__))
#define LOOP_56(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_55(BASE, DO, __VA_ARGS__))
#define LOOP_55(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_54(BASE, DO, __VA_ARGS__))
#define LOOP_54(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_53(BASE, DO, __VA_ARGS__))
#define LOOP_53(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_52(BASE, DO, __VA_ARGS__))
#define LOOP_52(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_51(BASE, DO, __VA_ARGS__))
#define LOOP_51(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_50(BASE, DO, __VA_ARGS__))
#define LOOP_50(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_49(BASE, DO, __VA_ARGS__))
#define LOOP_49(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_48(BASE, DO, __VA_ARGS__))
#define LOOP_48(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_47(BASE, DO, __VA_ARGS__))
#define LOOP_47(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_46(BASE, DO, __VA_ARGS__))
#define LOOP_46(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_45(BASE, DO, __VA_ARGS__))
#define LOOP_45(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_44(BASE, DO, __VA_ARGS__))
#define LOOP_44(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_43(BASE, DO, __VA_ARGS__))
#define LOOP_43(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_42(BASE, DO, __VA_ARGS__))
#define LOOP_42(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_41(BASE, DO, __VA_ARGS__))
#define LOOP_41(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_40(BASE, DO, __VA_ARGS__))
#define LOOP_40(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_39(BASE, DO, __VA_ARGS__))
#define LOOP_39(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_38(BASE, DO, __VA_ARGS__))
#define LOOP_38(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_37(BASE, DO, __VA_ARGS__))
#define LOOP_37(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_36(BASE, DO, __VA_ARGS__))
#define LOOP_36(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_35(BASE, DO, __VA_ARGS__))
#define LOOP_35(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_34(BASE, DO, __VA_ARGS__))
#define LOOP_34(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_33(BASE, DO, __VA_ARGS__))
#define LOOP_33(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_32(BASE, DO, __VA_ARGS__))
#define LOOP_32(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_31(BASE, DO, __VA_ARGS__))
#define LOOP_31(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_30(BASE, DO, __VA_ARGS__))
#define LOOP_30(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_29(BASE, DO, __VA_ARGS__))
#define LOOP_29(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_28(BASE, DO, __VA_ARGS__))
#define LOOP_28(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_27(BASE, DO, __VA_ARGS__))
#define LOOP_27(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_26(BASE, DO, __VA_ARGS__))
#define LOOP_26(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_25(BASE, DO, __VA_ARGS__))
#define LOOP_25(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_24(BASE, DO, __VA_ARGS__))
#define LOOP_24(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_23(BASE, DO, __VA_ARGS__))
#define LOOP_23(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_22(BASE, DO, __VA_ARGS__))
#define LOOP_22(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_21(BASE, DO, __VA_ARGS__))
#define LOOP_21(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_20(BASE, DO, __VA_ARGS__))
#define LOOP_20(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_19(BASE, DO, __VA_ARGS__))
#define LOOP_19(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_18(BASE, DO, __VA_ARGS__))
#define LOOP_18(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_17(BASE, DO, __VA_ARGS__))
#define LOOP_17(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_16(BASE, DO, __VA_ARGS__))
#define LOOP_16(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_15(BASE, DO, __VA_ARGS__))
#define LOOP_15(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_14(BASE, DO, __VA_ARGS__))
#define LOOP_14(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_13(BASE, DO, __VA_ARGS__))
#define LOOP_13(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_12(BASE, DO, __VA_ARGS__))
#define LOOP_12(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_11(BASE, DO, __VA_ARGS__))
#define LOOP_11(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_10(BASE, DO, __VA_ARGS__))
#define LOOP_10(BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_9( BASE, DO, __VA_ARGS__))
#define LOOP_9( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_8( BASE, DO, __VA_ARGS__))
#define LOOP_8( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_7( BASE, DO, __VA_ARGS__))
#define LOOP_7( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_6( BASE, DO, __VA_ARGS__))
#define LOOP_6( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_5( BASE, DO, __VA_ARGS__))
#define LOOP_5( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_4( BASE, DO, __VA_ARGS__))
#define LOOP_4( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_3( BASE, DO, __VA_ARGS__))
#define LOOP_4( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_3( BASE, DO, __VA_ARGS__))
#define LOOP_3( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) EXPAND(LOOP_2( BASE, DO, __VA_ARGS__))
#define LOOP_2( BASE, DO, VARS, ...) LOOP_1(BASE, DO, VARS) LOOP_1( BASE, DO, __VA_ARGS__)
#define LOOP_1( BASE, DO, VARS, ...) BASE(DO, VARS)
#define LOOP_0(BASE, DO, VARS, ...)