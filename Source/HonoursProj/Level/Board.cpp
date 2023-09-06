

#include "Board.h"

#include "AssetLoader_gen.h"

// Sets default values
ABoard::ABoard() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IconMesh"));
	BoardMesh->SetStaticMesh(Assets()->Mesh.PuzzleCube.Get());
	BoardMesh->SetWorldScale3D(FVector(1, 1, 0.01) * 10);
	BoardMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABoard::BeginPlay() {

}

// Called every frame
void ABoard::Tick(float DeltaTime) {

}
