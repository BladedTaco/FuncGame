#include "Type.h"

#include "Algo/AllOf.h"
#include "Algo/Compare.h"
#include "Algo/Transform.h"

#include "MyUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Determine the intersection of two types
EType Intersection(EType a, EType b) {
	if (a <= b) {
		return a;
	} else if (b <= a) {
		return b;
	}
	return EType::NONE;
}


UType::UType() {
	// Initialized Shared Colour Group
	if (!UType::SharedColourGroup) {
		UType::SharedColourGroup = NewObject<UColourGroup>();
	}
	ColourGroup = UType::SharedColourGroup;
}

// Test Compatibility
bool UType::Supercedes(const UType* other) const {
	EType myType = GetType();
	EType otherType = other->GetType();

	// Functor < any >  my
	// Number < int > other
	// my !< other
	// other !< my

	//UE_LOG(LogTemp, Warning, TEXT("%s ? %s"), *UEnum::GetValueAsString(myType), *UEnum::GetValueAsString(otherType));

	// ANY is guaranteed match
	if (myType == EType::ANY) { return true; }
	// No Match if Other isn't instance or same
	if (!(myType >= otherType)) { return false; }

	//UE_LOG(LogTemp, Warning, TEXT("%s >= %s"), *UEnum::GetValueAsString(myType), *UEnum::GetValueAsString(otherType));

	// Check Satisfies on all Template Pairs
	return Algo::CompareByPredicate(GetTemplates(), other->GetTemplates(myType), [](UType* a, UType* b) {
		return a->Supercedes(b);
	});
}


FString UType::ToString() const {
	// Get Base Type
	EType t = GetType();

	switch (t) {
	// Function
	case EType::FUNC: {
		auto templates = GetTemplates();
		FString fromStr, toStr;
		if (templates.Num() == 1) {
			fromStr = "?";
			toStr = templates[0]->ToString();
		} else {
			auto [from, to] = Destruct<2, TArray, UType*>(templates);
			fromStr = from->ToString();
			toStr = to->ToString();
		}
		return FString::Format(TEXT("({0} -> {1})"), { fromStr, toStr });
	}
	// Fallthrough
	default: break;
	}



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


bool UType::UnifyWith(UType* concreteType) {

#if 0 // For Debugging
	if (
		RecursiveCopy()->UnifyWith_Impl(concreteType->RecursiveCopy())
		!=
		VolatileConst()->UnifyWith_Impl(concreteType->VolatileConst())
	) {
		UE_LOG(LogTemp, Warning, TEXT("INVALIKD \n%s \n%s \n%s \n%s"),
			*RecursiveCopy()->ToString(),
			*VolatileConst()->ToString(),
			*concreteType->RecursiveCopy()->ToString(),
			*concreteType->VolatileConst()->ToString()
		);
		auto a = VolatileConst();
		auto b = concreteType->VolatileConst();
		a->UnifyWith_Impl(b);
	}
#endif

	// If Copies are Unifiable
	if (VolatileConst()->UnifyWith_Impl(concreteType->VolatileConst())) {
		// Unify Both Types
		return UnifyWith_Impl(concreteType);
	}
	return false;
}


bool UType::UnifyWith_Impl(UType* concreteType) {
	// Get Type Intersection
	EType inter = Intersection(GetType(), concreteType->GetType());
	if (inter == EType::NONE) return false;

	//if (!Supercedes(concreteType)) return false;
	auto otherTemplates = concreteType->GetTemplates(inter);
	auto myTemplates = GetTemplates(inter);
	if (otherTemplates.Num() == 0 || myTemplates.Num() == 0) return true;

	// Unify Colours
	GetColourGroup()->Unify(GetColourIndex(), concreteType->GetColourIndex());

	// Compare TEmpaltes
	return Algo::CompareByPredicate(myTemplates, otherTemplates, [](UType* a, UType* b) {
		return a->UnifyWith_Impl(b);
	});
}

FColor UType::GetColour() const {
	return GetColourGroup()->GetColour(GetColourIndex());
}

// Get Templates as Typeclass
TArray<UType*> UType::GetTemplates(ETypeClass As) const {
	auto templates = GetTemplates();

	// Check for special cases
	switch (GetType()) {
	case EType::FUNC:
		switch (As) {
		case ETypeClass::FUNCTOR: {
			auto [t0, t1] = Destruct<2, TArray, UType*>(templates);
			return { t1 };
		};
		default:
			return templates;	
		}
	}

	// Return templates as normal
	return templates;
}

// Get Templates as TypeData
TArray<UType*> UType::GetTemplates(ETypeData As) const {
	auto templates = GetTemplates();

	// Check for special cases
	switch (As) {
	case ETypeData::FUNC: 
		if (templates.Num() == 1) {
			return { UTypeVar::New(ETypeClass::ANY, false) , templates[0] };
		}
	default:
		return templates;
	}
	// Return templates as normal
	return templates;
}

TArray<UType*> UType::GetTemplates(EType As) const {
	if (IsETypeClass(As)) {
		return GetTemplates(( ETypeClass )As);
	} else if (IsETypeData(As)) {
		return GetTemplates(( ETypeData )As);
	}
	return GetTemplates();
}


UColourGroup* UType::GetColourGroup() const {
	//// Get Game Instance
	//if (auto Inst = Cast<UHonoursProjGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))) {
	//	// Return Colour Group
	//	return Inst->TypeVarColourGroup();
	//}
	return ColourGroup;
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
UType* UTypeConst::DeepCopy(TMap<UType*, UType*>& ptrMap) const {
	// Simply copy Type when terminal
	if (Terminal()) { 
		auto out = New(( ETypeBase )Type); 
		GetColourGroup()->ReferenceColour(ColourPtr, out->ColourPtr);
		return out;
	}

	// Create Copy and pass InType
	UTypeConst* out = New(( ETypeData )Type, {});
	// Recursively Copy InTemplates
	Algo::Transform(Templates, out->Templates, [&ptrMap](UType* t) { 
		return t->DeepCopy(ptrMap);
	});
	// Return copy
	return out;
}

int UTypeConst::GetColourIndex() const {
	return ColourPtr.IsValid() ? *ColourPtr : -1;
}

TSharedPtr<int> UTypeConst::ShareColour() const {
	return ColourPtr;
}

// Recursively Turn any InType into a constant
UTypeConst* UTypeConst::MakeConst(const UType* InType) {
	// Initialize a new TypeConst and give it its InType and colour after
	UTypeConst* out = UTypeConst::New(ETypeBase::NONE);
	out->Type = InType->GetType();
	out->Templates.Empty();

	// Const References Colour Only, rather than copying
	out->GetColourGroup()->ReferenceColour(InType->ShareColour(), out->ColourPtr);

	// Recursively Get the InType of all InTemplates
	Algo::Transform(InType->GetTemplates(), out->Templates, &UTypeConst::MakeConst);

	// Return the Fully Const InType
	return out;
}

// Constrict the Constant Type to the other InType
bool UTypeConst::RestrictTo(UType* other) {
	// Set InType to intersection of this InType and 
	Type = Intersection(Type, other->GetType());
	if (Type == EType::NONE) return false;


	// For each Template pair
	auto otherTemplates = other->GetTemplates(GetType());
	if (otherTemplates.Num() == 0) {
		// Copy Colours
		ColourPtr = other->ShareColour();
		return true;
	}

	for (int i = Templates.Num() - 1; i >= 0; i--) {
		// Get Template as Const Type
		auto t = Cast<UTypeConst>(Templates[i]);
		// If NonConst, Make Const
		if (!t) { Templates[i] = t = UTypeConst::MakeConst(t); }
		// Edit Type Recursively
		if (!t->RestrictTo(otherTemplates[i])) {
			return false;
		}
	}

	// Copy Colours
	ColourPtr = other->ShareColour();

	// return success
	return true;
	//Algo::CompareByPredicate(Templates, other->GetTemplates(GetType()), [](UType* me, UType* bound) {

	//})
}


void UTypeConst::BeginDestroy() {
	Super::BeginDestroy();

	//if (ColourPtr.IsValid()) {
	//	auto ref = ColourPtr.ToSharedRef();
	//	GetColourGroup()->FreeColour(MoveTemp(ref));
	//}
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
UType* UTypePtr::DeepCopy(TMap<UType*, UType*>& ptrMap) const {
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
		ptrMap.Add(Type, inner);
	}

	// Create InType, Deep Copying pointer
	UTypePtr* out = New(inner);
	out->CopyTemplates = CopyTemplates;
	// Recursively Copy InTemplates
	Algo::Transform(Templates, out->Templates, [&ptrMap](UType* t) {
		return t->DeepCopy(ptrMap);
	});
	return out;
}

bool UTypePtr::UnifyWith_Impl(UType* concreteType) {
	if (CopyTemplates) {
		// Copy Templates, require full unification
		if (!Get()->UnifyWith_Impl(concreteType)) return false;
	} else {
		// no copy templtes, only type matching
		UTypeConst* t = Get()->VolatileConst();
		t->Type = concreteType->GetType();
		if (!Get()->UnifyWith_Impl(t)) return false;

		//if (Intersection(Get()->GetType(), concreteType->GetType()) == EType::NONE) return false;
	}

	// Unify Colours
	GetColourGroup()->Unify(GetColourIndex(), concreteType->GetColourIndex());

	auto otherTemplates = concreteType->GetTemplates(GetType());
	auto myTemplates = UType::GetTemplates(GetType());
	return myTemplates.Num() == 0
		|| otherTemplates.Num() == 0
		|| Algo::CompareByPredicate(myTemplates, otherTemplates, [](UType* me, UType* other) {
			return me->UnifyWith_Impl(other);
		});
}

UType* UTypePtr::Get() {
	return Type;
}

int UTypePtr::GetColourIndex() const {
	if (Type) {
		return Type->GetColourIndex();
	}
	return -1;
}

TSharedPtr<int> UTypePtr::ShareColour() const {
	return Type ? Type->ShareColour() : TSharedPtr<int>();
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
	// Check for No Pointer
	if (!Type) return Templates;

	// Get Pointed to Templates
	auto templates = Type->GetTemplates(Type->GetType());

	// If Equal Numbers
	if (templates.Num() == Templates.Num()) {
		// Return based on CopyTemplates
		return CopyTemplates ? templates : Templates;
	}

	// If One is Zero
	if (templates.Num() * Templates.Num() == 0) {
		return templates.Num() == 0 ? Templates : templates;
	}

	// Else Handle Partial Pasting
	if (templates.Num() == 2 && Templates.Num() == 1) {
		return { templates[0], Templates[0] };
	}

	// Else fall through to own templates
	return Templates;
}

// Return Type Pointer has Valid Pointer
bool UTypePtr::Valid() const {
	return Type && IsValid(Type);
}


////// TYPE VARIABLE



// New Type Var
UTypeVar* UTypeVar::New(ETypeClass InType, bool bAssignColour) {
	// Create TypeVar
	UTypeVar* out = NewObject<UTypeVar>();
	out->Type = InType;

	// If Assigning Colour
	if (bAssignColour) {
		out->GetColourGroup()->NewColour(out->ColourIndex);
	}

	// Return TypeVar
	return out;
}

// Base Case of Deep Copy Recursion
UType* UTypeVar::DeepCopy(TMap<UType*, UType*>& ptrMap) const {
	//// Simply copy InType, Evidence is not copied
	//return New(Type);
	UTypeVar* out = New(Type, false);
	GetColourGroup()->DuplicateColour(ColourIndex, out->ColourIndex);
	// Apply all evidence as copy
	for (const auto &t : Evidence) {
		out->ApplyEvidence(t->DeepCopy(ptrMap));
	}
	return out;
}

FString UTypeVar::ToString() const {
	//ReapplyEvidence();
	return UType::ToString();
}

bool UTypeVar::UnifyWith_Impl(UType* concreteType) {
	bool success = ApplyEvidence(concreteType);
	
	// Unify Colours
	GetColourGroup()->Unify(GetColourIndex(), concreteType->GetColourIndex());

	ReapplyEvidence();

	for (auto& evidence : Evidence) {
		evidence->UnifyWith_Impl(Instance);
	}

	ReapplyEvidence();

	return success;
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

void UTypeVar::BeginDestroy() {
	GetColourGroup()->FreeColour(MoveTemp(ColourIndex));

	Super::BeginDestroy();

}

bool UTypeVar::ApplyEvidence(UType* InType) {
	UTypeConst* ConstIn = InType->VolatileConst();

	if (Instance && IsValid(Instance)) {
		// try to apply bound to copy, returning on failure
		auto copyInst = Cast<UTypeConst>(Instance->VolatileConst());
		if (!copyInst->RestrictTo(ConstIn)) return false;

		// Copy back to original instance on success
		Instance = copyInst;
	} else {
		// Instance becomes InType as UTypeConst
		Instance = ConstIn;
	}
	GetColourGroup()->Unify(Instance->GetColourIndex(), InType->GetColourIndex());

	// Add Evidence and Return Success
	Evidence.Add(InType);
	return true;
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
	for (auto& t : Evidence) {
		ApplyEvidence(t);
	}

	// Return Success
	return true;
}

void UTypeVar::ReapplyEvidence() {
	auto copy = Evidence;
	// Release Type Instance
	ResetEvidence();
	// Reapply all remaining evidence
	for (auto& t : copy) {
		ApplyEvidence(t);
	}
}

void UTypeVar::ResetEvidence() {
	GetColourGroup()->Split(*ColourIndex);
	Instance = NULL;
	Evidence = {};
}

int UTypeVar::GetColourIndex() const {
	return IsValid(Instance) ? Instance->GetColourIndex() : *ColourIndex;
}

TSharedPtr<int> UTypeVar::ShareColour() const {
	return IsValid(Instance) ? Instance->ShareColour() : ColourIndex;

	//return ColourIndex;
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

UType* UType::RecursiveCopy() {
	TMap<UType*, UType*> map = {};
	return DeepCopy(map);
}

UTypeConst* UType::VolatileConst() {
	return UTypeConst::MakeConst(this);
}
