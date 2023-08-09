#include "Types/TypeRepr.h"

#include "AssetLoader_gen.h"
#include "Types/Type.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Algo/Transform.h"
#include "Algo/Compare.h"

#include "Types/VStar.h"
#include "Types/Show.h"
#include "Types/Int_gen.h"
#include "Types/Maybe_gen.h"

#include "MyUtils.h"
#include <Components/TextRenderComponent.h>

// Sets default values for this component's properties
ATypeRepr::ATypeRepr()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = false;

	// ...

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundsComponent"));
	ChildBoundingPlanesParent = CreateDefaultSubobject<USceneComponent>(TEXT("ChildBoundingPlanesParent"));

	BoundingBox->SetupAttachment(RootComponent);

	ChildBoundingPlanesParent->SetupAttachment(RootComponent);

	ChildBoundingPlanesParent->SetAbsolute(false, false, false);
	ChildBoundingPlanesParent->SetComponentTickEnabled(false);
	UpdateComponentTransforms();

	SetActorEnableCollision(false);
}

void ATypeRepr::UpdateValue(VStar value) {
	if (!value.Valid()) return UpdateText("?");

	// Get the Type
	EType type = value.Type()->GetType();

	// Base Types
	if (IsETypeBase(type)
		//|| type == EType::NUMBER
		) {
		UpdateText(value.getTypeclass()->Show->show()(value));
		return;

	// Container Types
	} else if (IsETypeData(type)) {
		if (type == EType::NUMBER) {
			if (auto number = value.ResolveToSafe<Number<int>>()) {
				return UpdateText(number->GetTypeclass()->Show->show()(value));
			}
			if (auto number = value.ResolveToSafe<Number<float>>()) {
				return UpdateText(number->GetTypeclass()->Show->show()(value));
			}
		}

		// Maybe
		if (type == EType::MAYBE) {
			auto maybe = value.ResolveToSafe<MaybeV>();
			if (!maybe->_isNothing) {
				GetChildTypes()[0]->UpdateValue(maybe->_value);
				return;
			}
		}
		// Functions dont support concrete values

	// TypeClasses / incomplete types have no written values
	} // else...

	return UpdateText("?");
	
}

void ATypeRepr::UpdateText(FString text) {
	// Set all text components to given text
	for (auto plane : GetChildBoundingPlanes()) {
		if (auto textComp = Cast<UTextRenderComponent>(plane->GetChildComponent(0))) {
			textComp->SetText(text);
		}
	}

	// Recursively Update all Attached ATypeReprs
	TArray<AActor*> actors;
	GetAttachedActors(actors);
	for (AActor* actor : actors) {
		if (auto repr = Cast<ATypeRepr>(actor)) {
			repr->UpdateText(text);
		}
	}

}

TArray<UStaticMeshComponent*> ATypeRepr::GetChildBoundingPlanes() {
	// Initialize Arrays
	TArray<USceneComponent*> components;
	TArray<UStaticMeshComponent*> outComponents;

	// Populate Uncasted Components
	ChildBoundingPlanesParent->GetChildrenComponents(false, components);
	// Cast All Components into outComponents
	Algo::Transform(components, outComponents, [](USceneComponent* comp) {
		return Cast<UStaticMeshComponent>(comp);
	});

	// return casted components array
	return outComponents;
}

TArray<ATypeRepr*> ATypeRepr::GetChildTypes() {
	TArray<ATypeRepr*> typeReprs;
	for (auto* plane : GetChildBoundingPlanes()) {
		auto repr = Cast<ATypeRepr>(plane->GetAttachChildren()[0]->GetOwner());
		if (repr) {
			typeReprs.Add(repr);
		}
	}
	return typeReprs;
}

UClass* ATypeRepr::GetRepr(EType Type) {
	// If the ClassMap is Empty
	if (ATypeRepr::ClassMap.Num() == 0) {
		// Populate ClassMap
		const auto& TypeRepr = Assets()->TypeRepr;
		ATypeRepr::ClassMap = {
			{ EType::INT	, *TypeRepr.Int.Class		},
			{ EType::FLOAT	, *TypeRepr.Float.Class		},
			{ EType::BOOL	, *TypeRepr.Bool.Class		},
			{ EType::CHAR	, *TypeRepr.Char.Class		},
			{ EType::ANY	, *TypeRepr.Template.Class	},
			{ EType::MAYBE	, *TypeRepr.Maybe.Class		},
			{ EType::NUMBER	, *TypeRepr.Number.Class	},
			{ EType::FUNCTOR, *TypeRepr.Functor.Class	},
			{ EType::ORDINAL, *TypeRepr.Ordinal.Class	},
			{ EType::SHOW	, *TypeRepr.Show.Class		},
			{ EType::FUNC	, *TypeRepr.Function.Class	}
		};
	}

	// Use map to find and return relevant class
	UClass** res = ATypeRepr::ClassMap.Find(Type);
	UClass* out;
	if (!res) {
		out = *Assets()->TypeRepr.Template.Class;
	} else {
		out = *res;
	}

	return out;
}

ATypeRepr* ATypeRepr::CreateRepr(UType* Type, UWorld* World) {
	auto me = World->SpawnActor<ATypeRepr>(GetRepr(Type->GetType()));
	me->FullType = UTypeConst::MakeConst(Type);

	auto templates = Type->GetTemplates();
	auto planes = me->GetChildBoundingPlanes();

	// No Templates, Terminal Type
	if (templates.Num() == 0) {
		if (planes.Num() == 1) {
			planes[0]->SetVisibility(false);
		}

		// Handle TypeVar Colours
		if (Type->GetType() == EType::ANY) {
			FColor col = Type->GetColour();
			for (auto* comp : me->GetComponentsByClass(UStaticMeshComponent::StaticClass())) {
				Cast<UStaticMeshComponent>(comp)->SetVectorParameterValueOnMaterials("DiffuseColor", FVector(col.ReinterpretAsLinear()));
			}
		}	

		return me;
	}
	// MisMatch, Invalid Representation
	if (templates.Num() != planes.Num()) return nullptr;

	if (Type->GetType() == EType::NUMBER) {
		if (templates[0]->GetType() == EType::ANY) {
			planes[0]->SetVisibility(false);
			return me;
		} else {
			me->SetActorHiddenInGame(true);
		}
	}

	// For Each Template/Plane Pair
	for (int idx = templates.Num(); idx --> 0;) {
		// Create Specialized TypeRepr, and Fit it to Plane.
		auto repr = CreateRepr(templates[idx], World);
		FitActorToPlane(repr, repr->BoundingBox, planes[idx]);
		planes[idx]->SetVisibility(false);
	}

	return me;
}

void ATypeRepr::BeginDestroy() {
	DestroyChildren();
	Super::BeginDestroy();
}

void ATypeRepr::DestroyChildren() {
	// Destroy all Attached Actors
	TArray<AActor*> actors;
	GetAttachedActors(actors);
	for (AActor* actor : actors) {
		if (auto repr = Cast<ATypeRepr>(actor)) {
			repr->DestroyChildren();
		}
		actor->Destroy();
	}
}

ATypeRepr* ATypeRepr::UpdateRepr(UType* newType) {
	// Equal Types means no Change
	if (FullType->EqualTo(newType)) return this;
	
	DestroyChildren();
	Destroy();

	// Different Types, for now just recreate
	return CreateRepr(newType, GetWorld());
	
}
