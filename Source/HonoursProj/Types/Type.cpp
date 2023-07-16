#include "Types/Type.h"

#include "Algo/AllOf.h"
#include "Algo/Compare.h"
#include "Algo/Transform.h"



// Test Compatibility
bool UType::Supercedes(UType* other) const {
	EType myType = GetType();
	EType otherType = other->GetType();

	UE_LOG(LogTemp, Warning, TEXT("%s ? %s"), *UEnum::GetValueAsString(myType), *UEnum::GetValueAsString(otherType));

	// ANY is guaranteed match
	if (myType == EType::ANY) { return true; }
	// No Match on other strictly superceding this
	if (myType < otherType) { return false; }

	UE_LOG(LogTemp, Warning, TEXT("%s >= %s"), *UEnum::GetValueAsString(myType), *UEnum::GetValueAsString(otherType));

	// Check Satisfies on all Template Pairs
	return Algo::CompareByPredicate(GetTemplates(), other->GetTemplates(), [](UType* a, UType* b) {
		return a->Supercedes(b);
	});
}


FString UType::ToString() const {
	// Get Base Type
	EType t = GetType();
	FString type = UEnum::GetValueAsString(t).Replace(TEXT("EType::"), TEXT("")).ToLower();


	// Get Templates
	TArray<FString> templates;
	for (const UType* temp : GetTemplates()) {
		templates.Add(temp->ToString());
	}
	
	// Add Templates
	if (templates.Num() > 0) {
		type = type.Append("<");
		type = type.Append(FString::Join(templates, TEXT(", ")));
		type = type.Append(">");
	}

	return type;
}

bool UType::UnifyWith(const UType* concreteType) {
	if (GetType() != concreteType->GetType()) return false;

	auto templates = GetTemplates();
	auto otherTemplates = concreteType->GetTemplates();

	return Algo::CompareByPredicate(templates, otherTemplates, [](UType* a, UType* b) {
		return a->UnifyWith(b);
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
UType* UTypeConst::DeepCopy(const TMap<UType*, UType*>& ptrMap) const {
	// Simply copy Type when terminal
	if (Terminal()) { return New(( ETypeBase )Type); }

	// Create Copy and pass InType
	UTypeConst* out = New(( ETypeData )Type, {});
	// Recursively Copy InTemplates
	Algo::Transform(Templates, out->Templates, [&ptrMap](UType* t) { 
		return t->DeepCopy(ptrMap);
	});
	// Return copy
	return out;
}

// Recursively Turn any InType into a constant
UTypeConst* UTypeConst::MakeConst(const UType* InType) {
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
bool UTypeConst::Terminal() const {
	return Templates.Num() == 0;
}

// Return Type Directly
EType UTypeConst::GetType() const {
	return Type;
}

// Return Templates Directly
TArray<UType*> UTypeConst::GetTemplates() const {
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
UType* UTypePtr::DeepCopy(const TMap<UType*, UType*>& ptrMap) const {
	// Strip any Invalid ptrs 
	if (!Valid()) { return New(NULL); }

	// Get Pointed To UType
	UType* inner;

	// Check Typemap
	if (ptrMap.Contains(Type)) {
		inner = ptrMap[Type];
	// Else Deep Copy Type
	} else {
		inner = Type->DeepCopy(ptrMap);
	}

	// Create InType, Deep Copying pointer
	UTypePtr* out = New(inner);
	out->CopyTemplates = CopyTemplates;
	if (!CopyTemplates) {
		// Recursively Copy InTemplates
		Algo::Transform(Templates, out->Templates, [&ptrMap](UType* t) {
			return t->DeepCopy(ptrMap);
		});
	}
	return out;
}

bool UTypePtr::UnifyWith(const UType* concreteType) {
	return (
		UType::UnifyWith(concreteType) 
		|| (Templates.Num() == 0 && !CopyTemplates)
	) && Get()->UnifyWith(concreteType);
}

UType* UTypePtr::Get() {
	return Type;
}

// Return TypeVars Type
EType UTypePtr::GetType() const {
	if (Type) {
		return Type->GetType();
	} else {
		return EType::NONE;
	}
}

// Return TypeVars Templates
TArray<UType*> UTypePtr::GetTemplates() const {
	if (Type && CopyTemplates) {
		return Type->GetTemplates();
	}
	return Templates;
}

// Return Type Pointer has Valid Pointer
bool UTypePtr::Valid() const {
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
UType* UTypeVar::DeepCopy(const TMap<UType*, UType*>& ptrMap) const {
	//// Simply copy InType, Evidence is not copied
	//return New(Type);
	UTypeVar* out = New(Type);
	// Apply all evidence as copy
	for (const auto &t : Evidence) {
		out->ApplyEvidence(t->DeepCopy(ptrMap));
	}
	return out;
}

bool UTypeVar::UnifyWith(const UType* concreteType) {
	return ApplyEvidence(concreteType);
}


// Try to return Instances Type, Else return own Type
EType UTypeVar::GetType() const {
	if (Instance && IsValid(Instance)) {
		return Instance->GetType();
	}
	return ( EType )Type;
}

// Try to return Instances Templates, Else return nothing
TArray<UType*> UTypeVar::GetTemplates() const {
	if (Instance && IsValid(Instance)) {
		return Instance->GetTemplates();
	}
	return {};
}

bool UTypeVar::ApplyEvidence(const UType* InType) {
	UTypeConst* ConstIn = UTypeConst::MakeConst(InType);
	bool applicable = Supercedes(ConstIn);
	if (applicable) {
		Evidence.Add(ConstIn);
		if (Instance && IsValid(Instance)) {
			Instance->RestrictTo(ConstIn);
		} else {
			Instance = ConstIn;
		}
	}
	return applicable;
}

bool UTypeVar::RemoveEvidence(const UType* InType) {
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

void UTypeVar::ResetEvidence() {
	Instance = NULL;
	Evidence = {};
}


bool UType::EqualTo(const UType* other) const {
	// Ensure Type Equality
	if (GetType() != other->GetType()) return false;

	// Get Templates
	TArray<UType*> lhsT = GetTemplates();
	TArray<UType*> rhsT = other->GetTemplates();

	// Ensure Same Template Number
	if (lhsT.Num() != rhsT.Num()) { return false; }

	// Check All Templates
	for (int idx = lhsT.Num(); idx --> 0;) {
		if (!lhsT[idx]->EqualTo(rhsT[idx])) {
			// On mismatch, return unequal
			return false;
		}
	}

	// return equal
	return true;
}
