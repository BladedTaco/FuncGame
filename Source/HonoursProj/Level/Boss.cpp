// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Boss.h"

#include "Level/StatusBar.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABoss::Attack(AUnit* Target, float Damage) {

	if (IsValid(Target) && Target->bOnBoard) {
		Target->Health->CurrentValue -= Damage;
		return true;
	}

	return false;
}

