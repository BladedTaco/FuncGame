﻿#pragma once



//// Functor Instance Macro
#define SHOW(INST)		 \
PP__DIRECTIVE(Typeclass, Show, INST)

#define ISHOW() 											PP__NEWLINE \
class Show : public virtual IShow {							PP__NEWLINE \
private:													PP__NEWLINE \
	virtual FString _show( const VStar& me) const override;	PP__NEWLINE \
public:														PP__NEWLINE \
	Show() = default;										PP__NEWLINE \
}; 															PP__NEWLINE \
inline static const Show ShowInst = {};


#include "Show_gen.h"