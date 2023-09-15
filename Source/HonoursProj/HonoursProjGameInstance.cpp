// Fill out your copyright notice in the Description page of Project Settings.


#include "HonoursProjGameInstance.h"

UColourGroup* UHonoursProjGameInstance::TypeVarColourGroup() {
	// Return Cached Instance if Valid
	if (IsValid(TypeVarColourGroupInstance)) return TypeVarColourGroupInstance;
	// Else Create Instance
	TypeVarColourGroupInstance = NewObject<UColourGroup>(this, FName("TypeVarColourGroup"));
	// Return Instance
	return TypeVarColourGroupInstance;
}


// Cleanup. This acts as a quasi-destructor
void UHonoursProjGameInstance::Shutdown() {
	// Important, if you overwrite functionality in UE4.
	// Omitting this, may cause errors (depending on the class).
	Super::Shutdown();

	// PIE may cause this to be invalid. During the game, it will always be valid
	if (IsValid(TypeVarColourGroupInstance)) {
		// Cleanup

	}
}