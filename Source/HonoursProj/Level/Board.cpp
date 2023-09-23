

#include "Board.h"

#include "AssetLoader_gen.h"

#include "Components/BoxComponent.h"

// Sets default values
ABoard::ABoard() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot"));

	// Create static mesh component
	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->SetStaticMesh(Assets()->Mesh.PuzzleCube.Get());
	BoardMesh->SetWorldScale3D(FVector(1, 1, 0.01) * 10);
	BoardMesh->SetupAttachment(RootComponent);

	// Create box component
	MapBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("MapBounds"));
	MapBounds->SetWorldScale3D(FVector(1, 1, 0.01) * 10);
	MapBounds->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABoard::BeginPlay() {
	Super::BeginPlay();

	// Get Bounds
	FVector bounds = MapBounds->GetScaledBoxExtent();
	FVector minPos = MapBounds->GetComponentLocation() - bounds;
	float ZPos = MapBounds->GetComponentLocation().Z + 100;

	// Get XY Step/Start
	float XStep = 2 * bounds.Y / Width;
	float XStart = (XStep / 2) + minPos.Y;
	float YStep = 2 * bounds.X / Height;
	float YStart = (YStep / 2) + minPos.X;

	// Add All Positions
	for (int Y = 0; Y < Height; Y++) {
		for (int X = 0; X < Width; X++) {
			Positions.Add(FVector(YStart + Y * YStep, XStart + X * XStep, ZPos));
		}
	}
}

// Called every frame
void ABoard::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	static float IndexThreshold = 0.2f;
	IndexThreshold -= DeltaTime;

	if (IndexThreshold <= 0) {
		index = (index + 1) % Positions.Num();

		TestActor->SetActorLocation(Positions[index]);

		IndexThreshold = 0.2f;
	}
}

FVector ABoard::GetPosition(int X, int Y) {
	if (X == -1 && Y == -1) {
		return Positions[0] + (Positions[0] - Positions[Width + 1]);
	}

	// Handle bounds checking
	if (X < 0 || X > Width || Y < 0 || Y > Height) return FVector::ZeroVector;
	// Return Position
	return Positions[Y * Width + X];
}
