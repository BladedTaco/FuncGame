#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Types_gen.h"

#include "TypeRepr.generated.h"

class UType;
class UTypeConst;
class UStaticMeshComponent;
class UBoxComponent;
class VStar;


UCLASS( Blueprintable, Transient, DefaultToInstanced, ClassGroup=(Custom) )
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced)
		UTypeConst* FullType;

	// Updates Displayed Value
	void UpdateValue(VStar value);
	void UpdateText(FString text);

	// Get Bounding Planes
	TArray<UStaticMeshComponent*> GetChildBoundingPlanes();
	TArray<ATypeRepr*> GetChildTypes();

	void UpdateStencilValue(int32 InValue);

	// Get ATypeRepr subclass from EType
	static UClass* GetRepr(EType Type);

	// Create Full Representation from UType
	static ATypeRepr* CreateRepr(UType* Type, UWorld* World, int32 StencilValue = 255);

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;


	void DestroyChildren();

	ATypeRepr* UpdateRepr(UType* newType);

	void UpdateVisibility(bool NewVisibility);
};
