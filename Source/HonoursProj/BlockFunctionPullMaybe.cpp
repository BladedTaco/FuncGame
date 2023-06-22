// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionPullMaybe.h"


#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Components/TextRenderComponent.h"

void* ABlockFunctionPullMaybe::GetValue() {

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

	if (values.Num() == 0) {
		value = Maybe<int>::Nothing();
		TextComponent->SetText(FString(TEXT("Nothing")));
		return ( void* )&value;
	}

	auto i1 = values[0];

	value = Maybe<int>::Just(i1.get());

	TextComponent->SetText(FString::Format(TEXT("Just {0}"), { i1.get()}));

	return ( void* )&value;
}
