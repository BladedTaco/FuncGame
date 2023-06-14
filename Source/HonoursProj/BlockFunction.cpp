// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunction.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

// Called when the game starts or when spawned
void ABlockFunction::BeginPlay() {
	Super::BeginPlay();

	FAttachmentTransformRules attachRules = FAttachmentTransformRules(
		EAttachmentRule::KeepRelative, 
		EAttachmentRule::KeepRelative, 
		EAttachmentRule::KeepRelative,
		false
	);

	FVector origin, extent;
	GetActorBounds(true, origin, extent);

	FString name;
	FActorSpawnParameters params;
	for (FFuncConnector input : FunctionInputs) {
		name = FString::Format(TEXT("{0}_Input_{1}"), { GetFName().ToString(), input.Name });
		params.Name = FName(*name);
		AFunctionInput* actor = GetWorld()->SpawnActor<AFunctionInput>(params);
		actor->AttachToActor(this, attachRules);
		actor->SetActorRelativeLocation(FVector(0, -100, 2*extent.Z));
	}

	for (FFuncConnector output : FunctionOutputs) {
		name = FString::Format(TEXT("{0}_Output_{1}"), { GetFName().ToString(), output.Name });
		params.Name = FName(*name);
		AFunctionOutput* actor = GetWorld()->SpawnActor<AFunctionOutput>(params);
		actor->AttachToActor(this, attachRules);
		actor->SetActorRelativeLocation(FVector(0, 100, 2*extent.Z));
	}
}


void ABlockFunction::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Clicked %s"), *ClickedComponent->GetFName().ToString());

	TArray<AActor*> attached;
	GetAttachedActors(attached);
	for (AActor* actor : attached) {
		actor->Destroy();
	}
	Destroy();
}