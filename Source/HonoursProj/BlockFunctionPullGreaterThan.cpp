// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionPullGreaterThan.h"
#include "Types/Ord.h"
#include "Types/Int_gen.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Components/TextRenderComponent.h"


void* ABlockFunctionPullGreaterThan::GetValue() {
	auto myFunc = Ordinal<Number<int>>::gt<>;

	TArray<AActor*> actors, inputs;
	GetAttachedActors(actors);
	inputs = actors.FilterByPredicate([](const AActor* a) {
		return a->IsA<AFunctionInput>();
	});

	TArray<Number<int>> values;
	for (auto _input : inputs) {
		auto input = Cast<AFunctionInput>(_input);
		if (input->connectedTo) {
			AActor* o = input->connectedTo->GetAttachParentActor();
			auto other = Cast<ABlockFunctionPull>(o);
			void* v = other->GetValue();
			values.Add(*(Number<int>*)v);
		}
	}

	if (values.Num() < 2) {
		return ( void* )0;
	}

	auto i1 = values[0];
	auto i2 = values[1];

	bool res = myFunc(i1)(i2);

	TextComponent->SetText(FString::Format(TEXT("{0}"), { res }));

	return ( void* )res;
}
