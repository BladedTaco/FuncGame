#pragma once

#include "CoreMinimal.h"

template <typename EnumType>
class MaskedBitFlags {
private:
	// Stored Values
	EnumType Mask;
	EnumType Values;

public:
	// Constructors
	MaskedBitFlags(EnumType InMask, EnumType InValues)
		: Mask(InMask)
		, Values(InValues) {}
	// True/False only Constructor
	MaskedBitFlags(EnumType InValues, bool AllTrue = true)
		: Mask(InValues) {
		// Set Values Respectively
		Values = AllTrue ? InValues : ( EnumType )0;
	}

	// Actions
	constexpr bool Satisfies(EnumType InValues) const;
	EnumType Apply(EnumType InValues) const;
};

// Implementations

template<typename EnumType>
inline constexpr bool MaskedBitFlags<EnumType>::Satisfies(EnumType InValues) const {
	//		 Masked InValues  ==  Masked Values
	return  (InValues & Mask) == (Values & Mask);
}

template<typename EnumType>
inline EnumType MaskedBitFlags<EnumType>::Apply(EnumType InValues) const {
	InValues &= ~Mask;				// Empty out Mask region
	InValues |= (Values & Mask);	// Fill In relevant Values in Mask
	return InValues;				// Return Updated InValues
}