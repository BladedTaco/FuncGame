// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunction.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"

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

	FVector lower, upper, extent;
	GetBlockMesh()->GetLocalBounds(lower, upper);
	extent = (upper - lower) * GetBlockMesh()->GetComponentScale();

	int i = -1;
	FString name;
	FActorSpawnParameters params;
	for (FFuncConnector input : FunctionInputs) {
		i += 1;
		name = FString::Format(TEXT("{0}_Input_{1}"), { GetFName().ToString(), input.Name });
		params.Name = FName(*name);
		AFunctionInput* actor = GetWorld()->SpawnActor<AFunctionInput>(params);
		actor->AttachToActor(this, attachRules);
		actor->SetActorRelativeLocation(FVector(50*i, -100, 0.5 * extent.Z));
	}

	i = -1;
	for (FFuncConnector output : FunctionOutputs) {
		i += 1;
		name = FString::Format(TEXT("{0}_Output_{1}"), { GetFName().ToString(), output.Name });
		params.Name = FName(*name);
		AFunctionOutput* actor = GetWorld()->SpawnActor<AFunctionOutput>(params);
		actor->AttachToActor(this, attachRules);
		actor->SetActorRelativeLocation(FVector(50 * i, 100, 0.5 * extent.Z));
	}
}


AHonoursProjBlock* ABlockFunction::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	UE_LOG(LogTemp, Warning, TEXT("Clicked %s"), *ClickedComponent->GetFName().ToString());

	TArray<AActor*> attached;
	GetAttachedActors(attached);
	for (AActor* actor : attached) {
		actor->Destroy();
	}
	Destroy();
	return NULL;
}