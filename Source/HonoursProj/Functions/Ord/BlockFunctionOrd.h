// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockFunction.h"


#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "HUD/FunctionHUD.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Typeclass/Ordinal.h"
#include "Types/Dataclass/BaseTypes.h"

#include "MyUtils.h"

#include "AssetLoader_gen.h"



#include "BlockFunctionOrd.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HONOURSPROJ_API ABlockFunctionOrd : public ABlockFunction
{
	GENERATED_BODY()
public:
	ABlockFunctionOrd();

	// virtual Arr<VStarArray, VStarArrayReturn> GetInnerFunc() override;
	virtual void SetFunctionTypes() override;
};
