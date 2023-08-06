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

#include "Types/Unpack.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

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

	if (PanningCamera) {
		FVector newPos = MousePosScreen(GetWorld());

		
		AActor* camera = GetWorld()->GetFirstPlayerController()->GetViewTarget();
		camera->SetActorLocation(PanOrigin - newPos + PanOffset);

	}
}

void AHonoursProjPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LClick", EInputEvent::IE_Pressed, this, &AHonoursProjPawn::OnLClickPress);
	PlayerInputComponent->BindAction("LClick", EInputEvent::IE_Released, this, &AHonoursProjPawn::OnLClickRelease);

	PlayerInputComponent->BindAction("RClick", EInputEvent::IE_Pressed, this, &AHonoursProjPawn::OnRClickPress);
	PlayerInputComponent->BindAction("RClick", EInputEvent::IE_Released, this, &AHonoursProjPawn::OnRClickRelease);

	PlayerInputComponent->BindAction("MClick", EInputEvent::IE_Pressed, this, &AHonoursProjPawn::OnMClickPress);
	PlayerInputComponent->BindAction("MClick", EInputEvent::IE_Released, this, &AHonoursProjPawn::OnMClickRelease);

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





	//Number<int> k = { 1 };

	//Number<int> k1 = { 2 };

	//const IOrdinal* const io1 = k.Instances.Ordinal;

	//const IOrdinal* io2 = k.Instances.Ordinal;

	//const IOrdinal* io3 = Number<int>::Instances.Ordinal;
	//const IOrdinal* io4 = decltype(k)::Instances.Ordinal;
	//ORD or1 = io1->ord()(k)(k1);
	//ORD or2 = io2->ord()(k)(k1);
	//ORD or3 = io3->ord()(k)(k1);
	//ORD or4 = io3->ord()(k)(k1);

	//UE_LOG(LogTemp, Warning, TEXT("ORD TESTS %d %d %d %d"), or1, or2, or3, or4);




	VStar q1 = VStar(NumberV(1.5f));
	VStar q2 = VStar(NumberV(2.2f));
	VStar q3 = VStar(NumberV(3.3f));


	const IOrdinal* const qo1 = q1.getTypeclass()->Ordinal;

	Number<float> q5 = *q1.ResolveToSafe<Number<float>>();

	float q6 = q5.get();

	UE_LOG(LogTemp, Warning, TEXT("ORD VSTAR TESTS %f"), q6);

	ORD qor1 = qo1->ord()(q1)(q2);
	ORD qor2 = qo1->ord()(q2)(q3);
	ORD qor3 = qo1->ord()(q1)(q1);
	ORD qor4 = qo1->ord()(q3)(q1);

	UE_LOG(LogTemp, Warning, TEXT("ORD VSTAR TESTS %d %d %d %d"), qor1, qor2, qor3, qor4);


	Arr<int, int> square = { [](int a) { return a * a; } };

	ArrV Vsquare = { [=](VStar a) { return VStar(square(a.ResolveToUnsafe<int>())); } };

	 //Usage Example
	VStar ma1 = VStar(MaybeV::Just(4));
	VStar ma2 = VStar(MaybeV::Nothing());
	const IFunctor* const fo1 = ma1.getTypeclass()->Functor;
	const IFunctor* const fo2 = ma2.getTypeclass()->Functor;


	int a10 = ma1.ResolveToSafe<Maybe<int>>()->fromMaybe(-1);


	auto ma3 = ma2.ResolveToSafe<Maybe<int>>();

	int a11 = ma3->fromMaybe(-1);

	VStar a2 = fo1->fmap()(Vsquare)(ma1);
	VStar a3 = fo1->map_replace_by()(VStar(2))(ma1);
	
	int a4 = a2.ResolveToSafe<MaybeV>()->fromMaybe(-1);
	int a5 = a3.ResolveToSafe<MaybeV>()->fromMaybe(-1);

	VStar a6 = fo1->fmap()(Vsquare)(ma2);
	VStar a7 = fo1->map_replace_by()(VStar(2))(ma2);

	int a8 = a6.ResolveToSafe<MaybeV>()->fromMaybe(-1);
	int a9 = a7.ResolveToSafe<MaybeV>()->fromMaybe(-1);

	UE_LOG(LogTemp, Warning, TEXT("MAYBE VSTAR %d %d %d %d %d %d"), a4, a5, a8, a9, a10, a11);




	
	 //Usage Example
	Maybe<int> a = Maybe<int>::Just(4);
	a = Functor<Maybe<int>>::fmap<int>(square)(a);
	a = Functor<Maybe<int>>::map_replace_by<int>(2)(a);
	int q = fromMaybe<int>(0)(a);
	UE_LOG(LogTemp, Warning, TEXT("maybe %d"), q);

	//Maybe<int> l = a.fmap<int>(square)(a);

	//UE_LOG(LogTemp, Warning, TEXT("L %d"), l.fromMaybe(-1));

	UTypeConst* n = UTypeConst::New(ETypeData::MAYBE, { UTypeConst::New(ETypeData::NUMBER, {UTypeConst::New(ETypeBase::INT)}) });

	UTypeConst* g = FromType<Maybe<Number<int>>>();
	UTypeConst* g2 = FromType<int>();
	UTypeConst* g3 = FromType<float>();
	UTypeConst* g4 = FromType< Number<int>>();
	UTypeConst* g5 = FromType< Maybe<int>>();

	FString n_str = n->ToString();
	FString g_str = g->ToString();

	UE_LOG(LogTemp, Warning, TEXT("FromType Result %d %d %s, %s"), g->EqualTo(n), g5->EqualTo(n), *g_str, *n_str);





	//Number<int> n_i = { 1 };
	//Number<Number<int>> n_i_i = { Number<int>(2) };

	//NumberV l1 = { 1 };
	//NumberV l2 = { Number<int>(3) };
	//NumberV l3 = { n_i };
	//NumberV l4 = { n_i_i };



	//UE_LOG(LogTemp, Warning, TEXT("NumberVs")  );
	//UE_LOG(LogTemp, Warning, TEXT("n_i %d  ") ,n_i.get() );
	//UE_LOG(LogTemp, Warning, TEXT("n_i_i %d "),n_i_i.get().get());
	//UE_LOG(LogTemp, Warning, TEXT("n1 %d")    ,*l1.get<int>() );
	//UE_LOG(LogTemp, Warning, TEXT("n2 %d")    ,l2.get<Number<int>>()->get() );
	//UE_LOG(LogTemp, Warning, TEXT("n3 %d")    ,*l3.get<int>() );
	//UE_LOG(LogTemp, Warning, TEXT("n4 %d")    ,l4.get<Number<int>>()->get());


	//NumberV l5 = { l1 };
	//NumberV l6 = { l2 };

	//UE_LOG(LogTemp, Warning, TEXT("n5 %d"), *l5.get<int>());
	//UE_LOG(LogTemp, Warning, TEXT("n6 %d"), l6.get<Number<int>>()->get());

	//NumberV l7 = { std::move(l5) };

	//UE_LOG(LogTemp, Warning, TEXT("n6 %d"), *l7.get<NumberV>()->get<int>());
	//	
	//	

	/*UE_LOG(LogTemp, Warning, TEXT("NumberVs n_i %d  n_i_i %d n1 %d n2 %d n3 %d n4 %d"),
		n_i.get(),
		n_i_i.get().get(),
		l1.get<int>(),
		l2.get<Number<int>>().get(),
		l3.get<int>(),
		l4.get<Number<int>>().get()
	);
*/



	/*
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


	UE_LOG(LogTemp, Warning, TEXT("ORD %d %d %d %d"), n1, n2, n3, n4.get());*/

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

void AHonoursProjPawn::OnMClickPress() {
	PanningCamera = true;
	PanOrigin = GetWorld()->GetFirstPlayerController()->GetViewTarget()->GetActorLocation();
	PanOffset = MousePosScreen(GetWorld());
}

void AHonoursProjPawn::OnMClickRelease() {
	PanningCamera = false;
}

void AHonoursProjPawn::OnScroll(float axis) {
	if (-0.01 < axis && axis < 0.01) { return; }

	static UCameraComponent* camera = NULL;

	if (!camera) {
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), actors);
		for (AActor* actor : actors) {
			if (auto cam = Cast<ACameraActor>(actor)) {
				if (cam->HasActiveCameraComponent()) {
					camera = cam->GetCameraComponent();
					break;
				}
			}
		}
	}

	if (camera) {
		camera->SetOrthoWidth(camera->OrthoWidth * (100 - 10*axis)/100 );
	}



	//camera->SetActorLocation(camera->GetActorLocation() + FVector(axis * 100, 0, 0));

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