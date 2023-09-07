// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS(BlueprintType)
class HONOURSPROJ_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BoardMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* MapBounds;

	UPROPERTY(EditAnywhere)
	AActor* TestActor;


	UPROPERTY(EditAnywhere)
	int Width;

	UPROPERTY(EditAnywhere)
	int Height;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> Positions;

	UFUNCTION(BlueprintCallable)
	FVector GetPosition(int X, int Y);

	UPROPERTY(VisibleAnywhere)
	int index = 0;
};
