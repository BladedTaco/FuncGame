// Fill out your copyright notice in the Description page of Project Settings.

#include "Level/PartyMember.h"

#include "HonoursProjPawn.h"
#include "Engine/World.h"
#include "HonoursProjPlayerController.h"
#include "HonoursProjPawn.h"
#include "Camera/CameraComponent.h"

#include "Board.h"

// Sets default values
APartyMember::APartyMember()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void APartyMember::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APartyMember::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AHonoursProjBlock* APartyMember::HandleClick(UPrimitiveComponent* ClickedComponent) {
	// Get Camera
	AActor* camera = GetWorld()->GetFirstPlayerController()->GetPawn<AHonoursProjPawn>()->GetCamera()->GetOwner();

	// Move Camera
	FVector newLoc = camera->GetActorLocation();
	newLoc.Z = (GetActorLocation() + CameraStartPosition.GetLocation()).Z;
	camera->SetActorLocation(newLoc);

	// Move Board
	FVector boardLoc = Board->GetActorLocation();
	boardLoc.Z = newLoc.Z - 100;
	Board->SetActorLocation(boardLoc);

	// Dont Fire Release Events
	return nullptr;
}

