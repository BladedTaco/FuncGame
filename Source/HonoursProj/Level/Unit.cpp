#include "Level/Unit.h"

#include "StatusBar.h"

#include "AssetLoader_gen.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"


// Sets default values
AUnit::AUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	IconMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IconMesh"));
	IconMesh->SetStaticMesh(Assets()->Mesh.Cylinder.Get());
	IconMesh->SetupAttachment(RootComponent);


	// Handle Bars 
	// Create all Bars
	Health = CreateDefaultSubobject<UStatusBarComponent>("HealthBar");
	Mana = CreateDefaultSubobject<UStatusBarComponent>("ManaBar");
	Stamina = CreateDefaultSubobject<UStatusBarComponent>("StaminaBar");

	// Setup Attachments
	Health->SetupAttachment(RootComponent);
	Mana->SetupAttachment(RootComponent);
	Stamina->SetupAttachment(RootComponent);

	// Configure Bars
	Health->Configure(EStatusType::HEALTH, 100);
	Health->SetRelativeLocation(FVector::ForwardVector * -35);
	Mana->Configure(EStatusType::MANA, 100);
	Stamina->Configure(EStatusType::STAMINA, 100);
	Stamina->SetRelativeLocation(FVector::ForwardVector * 35);

	// Scale Block Mesh
	FVector min, max;
	GetBlockMesh()->GetLocalBounds(min, max);
	GetBlockMesh()->SetWorldScale3D(FVector(150, 850, 10) / (max - min));
	GetBlockMesh()->SetRelativeLocation(FVector::LeftVector * 300);
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	// Create Token
	TokenActor = GetWorld()->SpawnActor<AStaticMeshActor>();
	TokenActor->GetStaticMeshComponent()->SetStaticMesh(IconMesh->GetStaticMesh());

	// Disable Collision for all Meshes
	TArray<UStaticMeshComponent*> Meshes;
	GetComponents<UStaticMeshComponent>(Meshes);
	Meshes.Remove(GetBlockMesh());
	for (auto mesh : Meshes) {
		mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	}

}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Switch to Tab
AHonoursProjBlock* AUnit::HandleClick(UPrimitiveComponent* ClickedComponent) {



	return nullptr;
}

// Right Click is Left Click
AHonoursProjBlock* AUnit::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	return HandleClick(ClickedComponent);
}