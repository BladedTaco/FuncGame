// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HonoursProjPawn.h"
#include "HonoursProjBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


#include "Types/Functor.h"
#include "Types/Maybe_gen.h"
#include "Types/Ord.h"
#include "Types/Int_gen.h"
#include "Types/Types_gen.h"
#include "Types/Func_gen.h"

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

void AHonoursProjPawn::RemoveInactive() {
	// Remove Inactive Blocks
	SelectedBlocks.RemoveAll([](AHonoursProjBlock* block) {
		return !(block && IsValid(block) && block->bIsActive);
	});
}

void AHonoursProjPawn::OnLClickPress() {
	// Valid Block and Component
	if (CurrentBlockFocus && CurrentComponentFocus.IsValid()) {
		// Dispatch Click
		auto addBlock = CurrentBlockFocus->HandleClick(CurrentComponentFocus.Get());
		// Add the affected block
		if (!SelectedBlocks.Contains(addBlock)) {
			SelectedBlocks.Add(addBlock);
		}
	}
}

void AHonoursProjPawn::OnLClickRelease() {
	RemoveInactive();
	for (auto block : SelectedBlocks) {
		// Dispatch Click
		block->HandleClick(CurrentComponentFocus.Get());
	}
	RemoveInactive();


	Arr<int, int> square = { [](int a) { return a * a; } };
	
	 //Usage Example
	Maybe<int> a = Maybe<int>::Just(4);
	a = Functor<Maybe<int>>::fmap<int>(square)(a);
	a = Functor<Maybe<int>>::map_replace_by<int>(2)(a);
	int q = fromMaybe<int>(0)(a);
	UE_LOG(LogTemp, Warning, TEXT("maybe %d"), q);
	

	
	a = Maybe<int>::Nothing();
	a = Functor<Maybe<int>>::fmap<int>(square)(a);
	a = Functor<Maybe<int>>::map_replace_by<int>(2)(a);
	q = fromMaybe<int>(0)(a);
	UE_LOG(LogTemp, Warning, TEXT("maybe %d"), q);

	bool n1 = Ordinal<Number<int>>::lt<>(5)(6);
	bool n2 = Ordinal<Number<int>>::gt<>(6)(6);
	bool n3 = Ordinal<Number<int>>::eq<>(7)(6);
	Number<int> n4 = Ordinal<Number<int>>::min<>(5)(6);

	Arr<int, float> f = { [](int a) -> float { return 0.99 * a * a; } };
	Arr<float, int> f_a = { [](float a) -> int { return a * a; } };

	Arr<float, float> x = Functor<Arr<float, int>>::fmap<float>(f)(f_a);

	float f_r = f(2);
	int fa_r = f_a(2);
	float x_r = x(2);


	UE_LOG(LogTemp, Warning, TEXT("ARROW %f %d %f"), f_r, fa_r, x_r);


	UE_LOG(LogTemp, Warning, TEXT("ORD %d %d %d %d"), n1, n2, n3, n4.get());

	//UE_LOG(LogTemp, Warning, TEXT("ORD %d %d"), 
	//	Ordinal<Number<int>>::lt(5)(6),
	//	Ordinal<Number<int>>::lt(6)(4)
	//);


}

void AHonoursProjPawn::OnRClickPress(){
	// Valid Block and Component
	if (CurrentBlockFocus && CurrentComponentFocus.IsValid()) {
		// Dispatch Click
		auto addBlock = CurrentBlockFocus->HandleRClick(CurrentComponentFocus.Get());
		// Add the affected block
		if (!SelectedBlocks.Contains(addBlock)) {
			SelectedBlocks.Add(addBlock);
		}
	}
}

void AHonoursProjPawn::OnRClickRelease(){
	RemoveInactive();
	for (auto block : SelectedBlocks) {
		// Dispatch Click
		block->HandleRClick(CurrentComponentFocus.Get());
	}
	RemoveInactive();
}

void AHonoursProjPawn::OnScroll(float axis) {
	if (-0.01 < axis && axis < 0.01) { return; }

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