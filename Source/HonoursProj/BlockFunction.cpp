// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunction.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"
#include "FunctionConnector.h"

#include "MyUtils.h"

ABlockFunction::ABlockFunction() {
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextOutput"));
	TextComponent->SetText(FString("test"));
	TextComponent->SetRelativeLocation(FVector::UpVector * 200.0f);
	TextComponent->SetWorldRotation(FRotator(90, 0, 180));
	TextComponent->SetRelativeScale3D(FVector(10));
	TextComponent->SetupAttachment(GetBlockMesh());
}


// Called when the game starts or when spawned
void ABlockFunction::BeginPlay() {
	Super::BeginPlay();

	// Ensure Attachment is entirely KeepRelative
	FAttachmentTransformRules attachRules = FAttachmentTransformRules(
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		EAttachmentRule::KeepRelative,
		false
	);

	// Get Length from block center to top
	FVector lower, upper, extent;
	GetBlockMesh()->GetLocalBounds(lower, upper);
	extent = (upper - lower) * GetBlockMesh()->GetComponentScale();


	int idx;
	FString name;
	FActorSpawnParameters spawnParams;
	// Loop over both Inputs and Outputs
	for (auto [blockType, iterable, blocks, blockClass] : {
		MakeTuple(TEXT("Input"),  &Inputs,  (TArray<AFunctionConnector*>*)&InputBlocks,  AFunctionInput::StaticClass()),
		MakeTuple(TEXT("Output"), &Outputs, (TArray<AFunctionConnector*>*)&OutputBlocks, AFunctionOutput::StaticClass())
		}) {
			// Reset Index
		idx = 0;
		// For each of the Inputs/Outputs
		for (FParameter& param : *iterable) {
			// Set Actor Name
			name = FString::Format(TEXT("{0}_{1}_{2}"), { GetFName().ToString(), blockType, param.Name });
			spawnParams.Name = FName(*name);
			// Spawn Actor and give data
			AFunctionConnector* actor = GetWorld()->SpawnActor<AFunctionConnector>(blockClass, spawnParams);
			actor->ParameterInfo = FParameter(param.Name, UTypePtr::New(param.Type));
			blocks->Add(actor);
			// Attach to self
			actor->AttachToActor(this, attachRules);
			actor->SetActorRelativeLocation(FVector(100 * idx - 250, -100, 0.5 * extent.Z));
			// Iterate index
			idx += 1;
		}
	}
}

// Calculate Values
AHonoursProjBlock* ABlockFunction::HandleClick(UPrimitiveComponent* ClickedComponent) {
	GetValue();
	return this;
}

// Move
AHonoursProjBlock* ABlockFunction::HandleRClick(UPrimitiveComponent* ClickedComponent) {
	return AHonoursProjBlock::HandleClick(ClickedComponent);
}

// Resolve Type Signature
UType* ABlockFunction::ResolveType() {
	// Intiialize Output Arrow Terminal TypeVar
	UType* outArrow = UTypeVar::New(ETypeClass::ANY);

	// For Each Input
	for (AFunctionInput* input : InputBlocks) {
		// Try to Resolve precursors when a Connected Type
		if (!input->ResolveType()) {
			// On Resolution fail, Unconnected Type, Add Arrow Layer
			outArrow = UTypeConst::New(ETypeData::FUNC, { input->ParameterInfo.Type, UTypePtr::New(outArrow) });
		}
	}

	// Set OutputArrow
	OutputArrow = outArrow;
	return OutputArrow;
}