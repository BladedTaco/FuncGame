#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "StatusBar.generated.h"

class UMaterialInstanceDynamic;

// The Type of an FStatusBar
UENUM(BlueprintType)
enum class EStatusType : uint8 {
	UNIQUE	UMETA(DisplayName = "Unique"),
	HEALTH	UMETA(DisplayName = "Health"),
	MANA	UMETA(DisplayName = "Mana"),
	STAMINA	UMETA(DisplayName = "Stamina")
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UStatusBarComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	inline static TMap<EStatusType, FColor> ColourMap = {
		{ EStatusType::UNIQUE,	FColor::White	},
		{ EStatusType::HEALTH,	FColor::Red		},
		{ EStatusType::MANA,	FColor::Blue	},
		{ EStatusType::STAMINA,	FColor::Yellow	}
	};

	// Child Components
	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* BarMesh;

	UPROPERTY(VisibleAnywhere, Instanced)
	UStaticMeshComponent* BackingMesh;


	UMaterialInstanceDynamic* BarMaterial;

	// Value
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp)
	int CurrentValue;


	// Status Groups
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EStatusType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor Colour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

public:

	UFUNCTION(BlueprintCallable)
	float GetPercentage();

	// Configure the Component with Defaults
	void Configure(EStatusType InType, int InMaxValue, bool bStartsFull = true);
	void Configure(FString InName, FColor InColour, int InMaxValue, bool bStartsFull = true);

public:	
	// Sets default values for this component's properties
	UStatusBarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
		
	UPROPERTY(VisibleAnywhere)
	int LastValue;
};
