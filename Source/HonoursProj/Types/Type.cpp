#include "Types/Type.h"

#include "Algo/AllOf.h"
#include "Algo/Compare.h"
#include "Algo/Transform.h"



// Test Compatibility
bool UType::Supercedes(UType* other) {
	// ANY is guaranteed match
	if (GetType() == EType::ANY) { return true; }
	// No Match on differing Types
	if (GetType() < other->GetType()) { return false; }
	// Check Satisfies on all Template Pairs
	return Algo::CompareByPredicate(GetTemplates(), other->GetTemplates(), [](UType* a, UType* b) {
		return a->Supercedes(b);
	});
}

////// TYPE CONSTANT


// New TypeConst
UTypeConst* UTypeConst::New(ETypeData InType, TArray<UType*> InTemplates) {
	UTypeConst* out = NewObject<UTypeConst>();
	out->Type = ( EType )InType;
	out->Templates = InTemplates;
	return out;
}
UTypeConst* UTypeConst::New(ETypeBase InType) {
	UTypeConst* out = NewObject<UTypeConst>();
	out->Type = ( EType )InType;
	return out;
}

// Recursive Deep Copying
UType* UTypeConst::DeepCopy() {
	// Simply copy Type when terminal
	if (Terminal()) { return New(( ETypeBase )Type); }

	// Create Copy and pass InType
	UTypeConst* out = New(( ETypeData )Type, {});
	// Recursively Copy InTemplates
	Algo::Transform(Templates, out->Templates, [](UType* t) { 
		return t->DeepCopy(); 
	});
	// Return copy
	return out;
}

// Recursively Turn any InType into a constant
UTypeConst* UTypeConst::MakeConst(UType* InType) {
	// Initialize a new TypeConst and give it its InType after
	UTypeConst* out = UTypeConst::New(ETypeBase::NONE);
	out->Type = InType->GetType();

	// Recursively Get the InType of all InTemplates
	Algo::Transform(InType->GetTemplates(), out->Templates, &UTypeConst::MakeConst);

	// Return the Fully Const InType
	return out;
}


// Determine the intersection of two types
EType Intersection(EType a, EType b) {
	if (a <= b) {
		return a;
	} else if (b <= a) {
		return b;
	}
	return EType::NONE;
}

// Constrict the Constant Type to the other InType
void UTypeConst::RestrictTo(UType* other) {
	// Set InType to intersection of this InType and 
	Type = Intersection(Type, other->GetType());

	// For each Template pair
	auto otherTemplates = other->GetTemplates();
	for (int i = Templates.Num() - 1; i >= 0; i--) {
		// Get Template as Const Type
		auto t = Cast<UTypeConst>(Templates[i]);
		// If NonConst, Make Const
		if (!t) { Templates[i] = t = UTypeConst::MakeConst(t); }
		// Edit Type Recursively
		t->RestrictTo(otherTemplates[i]);
	}
}


// If there are no InTemplates
bool UTypeConst::Terminal() {
	return Templates.Num() == 0;
}

// Return Type Directly
EType UTypeConst::GetType() {
	return Type;
}

// Return Templates Directly
TArray<UType*> UTypeConst::GetTemplates() {
	return Templates;
}


////// TYPE POINTER

// New Type Pointer
UTypePtr* UTypePtr::New(UType* TypeVar, TArray<UType*> InTemplates) {
	UTypePtr* out = NewObject<UTypePtr>();
	out->Type = TypeVar;
	out->Templates = InTemplates;
	out->CopyTemplates = false;
	return out;
}
UTypePtr* UTypePtr::New(UType* TypeVar) {
	UTypePtr* out = UTypePtr::New(TypeVar, {});
	out->CopyTemplates = true;
	return out;
}

// Recursive Deep Copy
UType* UTypePtr::DeepCopy() {
	// Strip any Invalid ptrs 
	if (!Valid()) { return New(NULL); }

	// Create InType, Deep Copying pointer
	UTypePtr* out = New(Type->DeepCopy());
	out->CopyTemplates = CopyTemplates;
	if (!CopyTemplates) {
		// Recursively Copy InTemplates
		Algo::Transform(Templates, out->Templates, [](UType* t) {
			return t->DeepCopy();
		});
	}
	return out;
}

UType* UTypePtr::Get() {
	return Type;
}

// Return TypeVars Type
EType UTypePtr::GetType() {
	if (Type) {
		return Type->GetType();
	} else {
		return EType::NONE;
	}
}

// Return TypeVars Templates
TArray<UType*> UTypePtr::GetTemplates() {
	if (Type && CopyTemplates) {
		return Type->GetTemplates();
	}
	return Templates;
}

// Return Type Pointer has Valid Pointer
bool UTypePtr::Valid() {
	return Type && IsValid(Type);
}


////// TYPE VARIABLE



// New Type Var
UTypeVar* UTypeVar::New(ETypeClass InType) {
	UTypeVar* out = NewObject<UTypeVar>();
	out->Type = InType;
	return out;
}

// Base Case of Deep Copy Recursion
UType* UTypeVar::DeepCopy() {
	//// Simply copy InType, Evidence is not copied
	//return New(Type);
	UTypeVar* out = New(Type);
	// Apply all evidence as copy
	for (const auto &t : Evidence) {
		out->ApplyEvidence(t->DeepCopy());
	}
	return out;
}


// Try to return Instances Type, Else return own Type
EType UTypeVar::GetType() {
	if (Instance && IsValid(Instance)) {
		return Instance->GetType();
	}
	return ( EType )Type;
}

// Try to return Instances Templates, Else return nothing
TArray<UType*> UTypeVar::GetTemplates() {
	if (Instance && IsValid(Instance)) {
		return Instance->GetTemplates();
	}
	return {};
}

bool UTypeVar::ApplyEvidence(UType* InType) {
	bool applicable = Supercedes(InType);
	if (applicable) {
		Evidence.Add(InType);
		if (Instance && IsValid(Instance)) {
			Instance->RestrictTo(InType);
		} else {
			Instance = UTypeConst::MakeConst(InType);
		}
	}
	return applicable;
}

bool UTypeVar::RemoveEvidence(UType* InType) {
	// Track old number of Evidence
	int32 oldNum = Evidence.Num();
	// Filter out Evidence for invalid evidence and the specified Evidence
	Evidence = Evidence.FilterByPredicate([&](const UType* cand) {
		return cand && IsValid(cand) && cand != InType;
	});
	// Success is when *any* Evidence is removed
	if (Evidence.Num() == oldNum) { return false; }

	// Release Type Instance
	Instance = NULL;
	// Reapply all remaining evidence
	for (const auto& t : Evidence) {
		ApplyEvidence(t);
	}

	// Return Success
	return true;
}
