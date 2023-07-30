#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TypeRepr.generated.h"

class UStaticMeshComponent;


UCLASS( Blueprintable, ClassGroup=(Custom) )
class ATypeRepr : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ATypeRepr();

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
		TArray<UStaticMeshComponent*> MyTypeMeshes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
		TArray<UStaticMeshComponent*> ChildBoundingPlanes;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int MyMeshNumber = 0;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int ChildTypes = 0;
	
		
};
