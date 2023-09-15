#include "Utils/ColourGroup.h"

// Registers a New Colour
void UColourGroup::NewColour(int& Index) {
	ColourSet.Add(Index, NextColour());
}

// Frees up a Colour
void UColourGroup::FreeColour(int& Index) {
	// Valid Indices Only
	if (Index < 0) return;

	// Remove from Set and Push to Stack
	ColourStack.Add(ColourSet.Remove(Index));
}

bool UColourGroup::CopyColour(int Source, int& Dest) {
	// Find Colour
	FColor* Colour = ColourSet.Find(Source);

	// Return Failure
	if (!Colour) return false;

	FColor Copy = *Colour;
	Copy = FLinearColor::LerpUsingHSV(Copy, FColor::Black, 0.8).ToFColor(true);
	// Add and Unify
	ColourSet.Add(Dest, Copy);
	ColourSet.Union(Dest, Source);

	// Return Success
	return true;
}

// Returns the Colour at the Index, or Black if it doesn't exist
FColor UColourGroup::GetColour(int Index) {
	FColor* Colour = ColourSet.Find(Index);
	return Colour ? *Colour : FColor::Black;
}

// Joins two Colours
void UColourGroup::Unify(int A, int B) {
	ColourSet.Union(A, B);
}

// Makes A and B Different Colours
void UColourGroup::Split(int A, int B) {
	ColourSet.Split(A, B);
}

// Generates the Next Colour in the Sequence, or Pops from Returned Stack
FColor UColourGroup::NextColour() {
	// Pop from Colour Stack if possible
	if (ColourStack.Num() > 0) return ColourStack.Pop();
	
	// Else Generate next Colour based on Index
	int i = ColourIndex;
	ColourIndex++;

	// Split Range first on Colour, then Saturation, then Value
	// i = [As Bits] Ignored ... VVV SSS CCC CCC
	return FLinearColor::MakeFromHSV8(
			   SplitRange( i		& 63U, 0, 255),
		255U - SplitRange((i >> 6)	& 7U , 0, 80 ),
		255U - SplitRange((i >> 9)  & 7U , 0, 80 )
	).ToFColor(true);
}

// Splits A range fairly based on an index in a binary search fashion
int UColourGroup::SplitRange(int Index, int Min, int Max) {
	// 0 Index is Min output
	if (Index == 0) return Min;

	// Iteratively Half range based on binary digits
	while (Index > 0) {
		// Based on Last Digit
		if (Index & 1) {
			// Shrink Max on Odd
			Max -= (Max - Min) / 2;
		} else {
			// Grow Min on Even
			Min += (Max - Min) / 2;
		}
		// Next Digit
		Index >>= 1;
	}

	// Return Middle of Range
	return (Min + Max) / 2;
}
