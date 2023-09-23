// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"

#include "PuzzleLevelActor.generated.h"

class ULevelSequence;
class ULevelSequencePlayer;

class APartyMember;
class ABoss;

class UStaticMeshComponent;

UCLASS()
class HONOURSPROJ_API APuzzleLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleLevelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	ULevelSequence* TestSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQualifiedFrameTime TestStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<APartyMember*> Party;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ABoss* Boss;
public:

	// Level Sequence Control
	UFUNCTION(BlueprintCallable, Category = "Level Sequence")
	void MarkTestStart();

	UFUNCTION(BlueprintCallable, Category = "Level Sequence")
	void RunTest();

	UFUNCTION(BlueprintCallable, Category = "Level Sequence")
	void FailTest();

	UFUNCTION(BlueprintCallable, Category = "Level Sequence")
	bool EndTest();

protected:

	UPROPERTY(VisibleAnywhere)
	ULevelSequencePlayer* SequenceObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TestSuccess;

	UPROPERTY(EditAnywhere)
	FVector StartLocation;

};


/*
Design docs

Make a boss object that exposes the attacks, etc it can do
Use a Test Level Sequnce to Activate these functions
Add an actor for the players units, and have the boss attacks affect these units

at the end of a test sequence, test the players to see if they pass the value test
If not, undo all boss effects / reset unit values

*/