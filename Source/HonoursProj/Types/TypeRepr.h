#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Types/Types_gen.h"

#include "TypeRepr.generated.h"

class UType;
class UStaticMeshComponent;


UCLASS( Blueprintable, ClassGroup=(Custom) )
class ATypeRepr : public AActor
{
	GENERATED_BODY()

private:
	inline static TMap<EType, UClass*> ClassMap = {};
public:	
	// Sets default values for this component's properties
	ATypeRepr();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* ChildBoundingPlanesParent;

	// Get Bounding Planes
	TArray<UStaticMeshComponent*> GetChildBoundingPlanes();

	// Get ATypeRepr subclass from EType
	static UClass* GetRepr(EType Type);

	// Create Full Representation from UType
	static ATypeRepr* CreateRepr(UType* Type, UWorld* World);

};
