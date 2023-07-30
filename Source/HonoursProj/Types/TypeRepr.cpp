#include "Types/TypeRepr.h"

// Sets default values for this component's properties
ATypeRepr::ATypeRepr()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = false;

	// ...

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ATypeRepr::OnConstruction(const FTransform& Transform) {
	int i;
	for (i = MyMeshNumber; i-- > 0;) {
		MyTypeMeshes.Add(CreateDefaultSubobject<UStaticMeshComponent>(NAME_None));
	}
	for (i = ChildTypes; i-- > 0;) {
		ChildBoundingPlanes.Add(CreateDefaultSubobject<UStaticMeshComponent>(NAME_None));
	}
}

