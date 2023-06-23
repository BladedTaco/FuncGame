// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionPull.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

ABlockFunctionPull::ABlockFunctionPull() {
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextOutput"));
	TextComponent->SetText(FString("test"));
	TextComponent->SetRelativeLocation(FVector::UpVector * 200.0f);
	TextComponent->SetWorldRotation(FRotator(90, 0, 180));
	TextComponent->SetRelativeScale3D(FVector(10));
	TextComponent->SetupAttachment(GetBlockMesh());
}

// Pull Otuput
AHonoursProjBlock* ABlockFunctionPull::HandleClick(UPrimitiveComponent* ClickedComponent) {
	GetValue();
	return this;

	//Function<void*, void*> myFunc = InnerFunction;

	//TArray<AActor*> actors, inputs, outputs;
	//GetAttachedActors(actors);
	//inputs = actors.FilterByPredicate([](const AActor& a) {
	//	a.IsA<AFunctionInput>();
	//});
	//outputs = actors.FilterByPredicate([](const AActor& a) {
	//	a.IsA<AFunctionInput>();
	//});


	//for (auto _input : inputs) {
	//	auto input = Cast<AFunctionInput>(_input);
	//	if (input->connectedTo) {
	//		AActor* o = input->connectedTo->GetAttachParentActor();
	//		auto other = Cast<ABlockFunctionPull>(o);
	//		void* v = other->GetValue();
	//		myFunc = myFunc(v);
	//	}
	//}

	//// Output Only
	//if (FunctionInputs.Num() == 0) {

	//} 


	//return nullptr;
}


// Move
AHonoursProjBlock* ABlockFunctionPull::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	return AHonoursProjBlock::HandleClick(ClickedComponent);
}

