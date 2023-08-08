#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Types/Types_gen.h"

#include "TypeRepr.generated.h"

class UType;
class UStaticMeshComponent;
class UBoxComponent;
class VStar;


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BoundingBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EType Type;

	// Updates Displayed Value
	void UpdateValue(VStar value);
	void UpdateText(FString text);

	// Get Bounding Planes
	TArray<UStaticMeshComponent*> GetChildBoundingPlanes();
	TArray<ATypeRepr*> GetChildTypes();


	// Get ATypeRepr subclass from EType
	static UClass* GetRepr(EType Type);

	// Create Full Representation from UType
	static ATypeRepr* CreateRepr(UType* Type, UWorld* World);

};
