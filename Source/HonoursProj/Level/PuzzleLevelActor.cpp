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

	//if (TestStart.Time.FrameNumber != StartTime.Time.FrameNumber) {
	// Set Start Time

	if (TestStart.Time.FrameNumber <= StartTime.Time.FrameNumber) {
		TestStart = StartTime;

		// Jump to Loop Start 
		SequenceObject->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(LoopStart.Time.FrameNumber, EUpdatePositionMethod::Play));
		SequenceObject->Play();
	}
	//}
}

void APuzzleLevelActor::MarkLoopStart() {
	auto StartTime = SequenceObject->GetCurrentTime();

	// Save Last LoopStart
	if (LoopStart.Time.FrameNumber > FallbackLoopStart.Time.FrameNumber) FallbackLoopStart = LoopStart;

	LoopStart = StartTime;
	SequenceObject->Play();
}

void APuzzleLevelActor::RunTest() {
	// Skip on Test earlier than current time
	if (TestStart.Time.FrameNumber < SequenceObject->GetCurrentTime().Time.FrameNumber) return;

	// Set Initial Aggregate Test Success
	TestSuccess = true;

	//// Play to Test End
	// play
	SequenceObject->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(TestStart.Time.FrameNumber - 1, EUpdatePositionMethod::Play));
	SequenceObject->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(TestStart.Time.FrameNumber + 1, EUpdatePositionMethod::Jump));
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

	//if (LoopStart.Time > TestStart.Time) {
	//	LoopStart = FallbackLoopStart;
	//}


	// Jump Back to Start, undoing effects
	SequenceObject->Pause();
	SequenceObject->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(LoopStart.Time, EUpdatePositionMethod::Jump));
	SequenceObject->Play();

	// Return Test Failure
	return false;
}

