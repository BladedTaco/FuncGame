#include "BlockFunctionCounter.h"


#include "Engine/World.h"


#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Types/Types_gen.h"
#include "Types/Type.h"

#include "Types/Functor.h"
#include "Types/Show.h"
#include "Types/Maybe_gen.h"
#include "Types/Func_gen.h"
#include "Types/Int_gen.h"

#include "MyUtils.h"


#include "HUD/FunctionHUD.h"
#include "BlockFunctionCounter.h"

#include "Algo/AllOf.h"
#include "Kismet/GameplayStatics.h"

void ABlockFunctionCounter::SetFunctionTypes() {

	FunctionName = FString(TEXT("Counter"));

	Outputs = {
		{"Counter", UTypeConst::New(ETypeData::NUMBER, { UTypeConst::New(ETypeBase::INT) }) }
	};

}

Arr<VStarArray, VStarArrayReturn> ABlockFunctionCounter::GetInnerFunc() {
	return Arr<VStarArray, VStarArrayReturn>([this](VStarArray values) -> VStarArrayReturn {

		VStar out = VStar(NumberV((int)CurrentValue));

		// Show
		const IShow* const show = out.getTypeclass()->Show;
		this->HUD.Instance->LastResult = show->show()(out);

		return { out };

	});
}

void ABlockFunctionCounter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

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
