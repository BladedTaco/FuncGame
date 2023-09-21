#include "BlockFunctionCounter.h"


#include "Engine/World.h"


#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Typeclass/Functor.h"
#include "Types/Typeclass/Show.h"
#include "Types/Dataclass/Maybe_gen.h"
#include "Types/Dataclass/BaseTypes.h"

#include "MyUtils.h"


#include "HUD/FunctionHUD.h"
#include "BlockFunctionCounter.h"

#include "Algo/AllOf.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

#include "AssetLoader_gen.h"

// Set Function Icon Mesh
ABlockFunctionCounter::ABlockFunctionCounter() {
	FunctionIcon->SetStaticMesh(Assets()->Icon.Counter.Get());
}

void ABlockFunctionCounter::SetFunctionTypes() {

	FunctionName = FString(TEXT("Counter"));

	Outputs = {
		{"Counter",  UTypeConst::New(ETypeBase::INT) }
	};

}


Arr<VStarArray, VStarArrayReturn> ABlockFunctionCounter::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar out = VStar(Int((int)CurrentValue));

		// Show
		const IShow* const show = out.getTypeclass()->Show;
		this->HUD.Inst()->LastResult = show->show()(out);

		return { out };

	});
}

void ABlockFunctionCounter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GEngine && GIsEditor && !GWorld->HasBegunPlay()) return;

	float NextValue = CurrentValue + DeltaTime * TickRate;

	if (FMath::Fmod(CurrentValue, 1.0f) > FMath::Fmod(NextValue, 1.0f)) {
		// Propogate Update
		PropagateToEnds({ EPropagable::GETVALUE });

		// Old system

		//TArray<AActor*> actors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlockFunction::StaticClass(), actors);

		//for (AActor* act : actors) {
		//	auto func = Cast<ABlockFunction>(act);

		//	if (func && (func->OutputBlocks.Num() == 0 || Algo::AllOf(func->OutputBlocks, [](const AFunctionOutput* outBlock) {
		//		return outBlock->connectedTo.Num() == 0;
		//	}))) {
		//		if (func->InputBlocks.Num() == 0 || Algo::AllOf(func->InputBlocks, [](const AFunctionInput* inBlock) {
		//			return !!inBlock->connectedTo;
		//		})) {
		//			func->GetValue();
		//		}
		//	}
		//}
	}

	CurrentValue = FMath::Fmod(NextValue, MaxValue);

}
