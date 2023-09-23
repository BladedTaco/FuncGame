// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleLevelActor.h"


#include "AssetLoader_gen.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APuzzleLevelActor::APuzzleLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IconMesh"));
	Mesh->SetStaticMesh(Assets()->Mesh.PuzzleCube.Get());
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APuzzleLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();

	if (!IsValid(SequenceObject)) {
		// Create Level Sequence Player
		ALevelSequenceActor* SeqActor;
		FMovieSceneSequencePlaybackSettings settings;
		settings.bAutoPlay = false;
		SequenceObject = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), TestSequence, settings, SeqActor);
	}
}

// Called every frame
void APuzzleLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (IsValid(SequenceObject)) {
	//	double lerpVal = SequenceObject->GetCurrentTime().AsSeconds();
	//	SetActorLocation(StartLocation + 400 * lerpVal * FVector::RightVector);
	//}
}

void APuzzleLevelActor::MarkTestStart() {

	auto StartTime = SequenceObject->GetCurrentTime();

	if (TestStart.Time.FrameNumber != StartTime.Time.FrameNumber) {
		// Set Start Time
		TestStart = StartTime;
		// Pause Sequence
		SequenceObject->Pause();
	}
}

void APuzzleLevelActor::RunTest() {

	// Set Initial Aggregate Test Success
	TestSuccess = true;

	//// Play to Test End
	// play
	SequenceObject->Play();
}

void APuzzleLevelActor::FailTest() {
	TestSuccess = false;
}

bool APuzzleLevelActor::EndTest() {

	if (!IsValid(SequenceObject)) return false;

	// If No Tests Failed
	if (TestSuccess) {
		// keep playing
		//// End the Sequence
		//SequenceObject->GoToEndAndStop();
		//SequenceObject = NULL;
		return true;
	}


	// Jump Back to Start, undoing effects
	SequenceObject->Pause();
	SequenceObject->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(TestStart.Time, EUpdatePositionMethod::Play));

	// Return Test Failure
	return false;
}

