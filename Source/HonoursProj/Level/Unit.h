#pragma once

#include "CoreMinimal.h"
#include "HonoursProjBlock.h"
#include "Unit.generated.h"


// Forward Declarations
class UStaticMeshComponent;
class AStaticMeshActor;
class UStatusBarComponent;
class ABoard;


// A Unit on the Game Board
UCLASS(Blueprintable, BlueprintType, Abstract)
class HONOURSPROJ_API AUnit : public AHonoursProjBlock {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interaction Handlers
	virtual AHonoursProjBlock* HandleClick(UPrimitiveComponent* ClickedComponent) override;
	virtual AHonoursProjBlock* HandleRClick(UPrimitiveComponent* ClickedComponent) override;

	bool TrySetPosition(int X, int Y);

public:
	// Configurables
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* IconMesh;

	UPROPERTY(EditAnywhere)
	AStaticMeshActor* TokenActor;

	UPROPERTY(EditDefaultsOnly)
	FString Name;


	//Status Bars
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStatusBarComponent* Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStatusBarComponent* Mana;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStatusBarComponent* Stamina;

	// Board
	UPROPERTY(EditAnywhere)
	ABoard* Board;

	UPROPERTY(VisibleAnywhere)
	FVector2D Position;
};
