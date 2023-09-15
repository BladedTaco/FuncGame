#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "UnionFindSplit.hpp"

#include "ColourGroup.generated.h"

UCLASS(BlueprintType)
class UColourGroup : public UObject
{
	GENERATED_BODY()

public:
	// Adding / Removing Colours
	void NewColour(int& Index);
	void FreeColour(int& Index);
	bool CopyColour(int Source, int& Dest);

	// Handling Colours
	FColor GetColour(int Index);
	void Unify(int A, int B);
	void Split(int A, int B);


private:
	UPROPERTY(VisibleAnywhere)
	int ColourIndex = 0;

	// Colour Space
	UnionFindSplit<FColor> ColourSet;
	// Freed Colours
	TArray<FColor> ColourStack;

	// Generates new Colour or gives up Freed Colour
	FColor NextColour();
	// Splits a Range in a Binary Search Midpoint Fashion
	static int SplitRange(int Index, int Min, int Max);
};
