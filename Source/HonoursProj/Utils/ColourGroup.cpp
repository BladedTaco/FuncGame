#include "Utils/ColourGroup.h"

#include "Engine.h"

UColourGroup::UColourGroup() {
	ColourStack = {};
	ColourSet = {};
}

// Registers a New Colour
void UColourGroup::NewColour(TSharedRef<int> Index) {
	ColourSet.Add(Index, NextColour());
}

// Frees up a Colour
void UColourGroup::FreeColour(TSharedRef<int>&& Index) {
	// Valid Indices Only
	if (*Index < 0) return;
	
	// Pop from Set
	FColor Popped = ColourSet.Remove(MoveTemp(Index));
	// If No longer in Set
	if (ColourSet.Contains([Popped](const FColor& Colour) { return Colour == Popped; })) return;

	// Push to Stack for Re-use
	ColourStack.Add(Popped);

	CheckGarbageCollect();
}

bool UColourGroup::ReferenceColour(TSharedRef<int> Source, TSharedRef<int>& Dest) {
	// Simply Copy Index Pointer
	TSharedRef<int> copy = Dest;
	FreeColour(MoveTemp(copy));
	*Dest = -1;
	Dest = Source;

	return true;

	//// Find Colour
	//FColor* Colour = ColourSet.Find(*Source);

	//// Return Failure
	//if (!Colour) return false;

	//FColor Copy = *Colour;
	//Copy = FLinearColor::LerpUsingHSV(Copy, FColor::Black, 0.8).ToFColor(true);
	//// Add and Unify
	//ColourSet.Add(Dest, Copy);
	//ColourSet.Union(*Dest, *Source);

	//// Return Success
	//return true;
}

bool UColourGroup::ReferenceColour(TSharedPtr<int> Source, TSharedPtr<int>& Dest) {
	if (!Source.IsValid()) return false;

	if (Dest.IsValid()) {
		TSharedRef<int> copy = Dest.ToSharedRef();
		FreeColour(MoveTemp(copy));
		*Dest = -1;
	}
	Dest = Source;
	return true;
}

bool UColourGroup::DuplicateColour(TSharedRef<int> Source, TSharedRef<int> Dest) {
	// Find Colour
	FColor* Colour = ColourSet.Find(*Source);

	CheckGarbageCollect();

	// Return Failure
	if (!Colour) return false;

	// Add Copy
	ColourSet.Add(Dest, *Colour);

	// Return Success
	return true;
}

bool UColourGroup::DuplicateColour(TSharedPtr<int> Source, TSharedPtr<int>& Dest) {
	if (!Source.IsValid()) return false;
	if (!Dest.IsValid()) Dest = MakeShareable(new int(-1));
	return DuplicateColour(Source.ToSharedRef(), Dest.ToSharedRef());
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

	CheckGarbageCollect();
}

void UColourGroup::Split(int A) {
	ColourSet.Split(A);

	CheckGarbageCollect();
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

void UColourGroup::CheckGarbageCollect() {
	// Garbage Collect every 500 calls
	if (++GarbageCollectCounter < 5000) return;
	GarbageCollectCounter = 0;

	if (GEngine) {
		GEngine->ForceGarbageCollection();
	}
}
