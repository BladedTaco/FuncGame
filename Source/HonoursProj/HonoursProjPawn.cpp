// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonoursProjPawn.h"
#include "HonoursProjBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AHonoursProjPawn::AHonoursProjPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AHonoursProjPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);
		TraceForBlock(Start, End, false);
	}
}

void AHonoursProjPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LClick", EInputEvent::IE_Pressed, this, &AHonoursProjPawn::OnLClickPress);
	PlayerInputComponent->BindAction("LClick", EInputEvent::IE_Released, this, &AHonoursProjPawn::OnLClickRelease);

	PlayerInputComponent->BindAction("RClick", EInputEvent::IE_Pressed, this, &AHonoursProjPawn::OnRClickPress);
	PlayerInputComponent->BindAction("RClick", EInputEvent::IE_Released, this, &AHonoursProjPawn::OnRClickRelease);

	PlayerInputComponent->BindAxis("Scroll", this, &AHonoursProjPawn::OnScroll);
}

void AHonoursProjPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}


void AHonoursProjPawn::OnLClickPress() {
	// Valid Block and Component
	if (CurrentBlockFocus && CurrentComponentFocus.IsValid()) {
		// Dispatch Click
		CurrentBlockFocus->HandleClick(CurrentComponentFocus.Get());
	}
}
void AHonoursProjPawn::OnLClickRelease() {
	OnLClickPress();
}
void AHonoursProjPawn::OnRClickPress(){
	// Valid Block and Component
	if (CurrentBlockFocus && CurrentComponentFocus.IsValid()) {
		// Dispatch Click
		CurrentBlockFocus->HandleRClick(CurrentComponentFocus.Get());
	}
}
void AHonoursProjPawn::OnRClickRelease(){
}

void AHonoursProjPawn::OnScroll(float axis) {
	if (-0.01 < axis && axis < 0.01) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Scroll %f"), axis);

	//SetActorLocation(GetActorLocation() + FVector(axis * 100, 0, 0));

	//APlayerCameraManager* camera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	AActor* camera = GetWorld()->GetFirstPlayerController()->GetViewTarget();

	camera->SetActorLocation(camera->GetActorLocation() + FVector(axis * 100, 0, 0));

	

}

void AHonoursProjPawn::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		AHonoursProjBlock* HitBlock = Cast<AHonoursProjBlock>(HitResult.Actor.Get());
		CurrentComponentFocus = HitResult.Component;
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(true);
			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}