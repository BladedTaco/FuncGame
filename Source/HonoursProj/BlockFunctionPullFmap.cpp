// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionPullFmap.h"

#include "Types/Ord.h"
#include "Types/Int_gen.h"

#include "FunctionInput.h"
#include "FunctionOutput.h"

#include "Components/TextRenderComponent.h"

void* ABlockFunctionPullFmap::GetValue() {

	return ( void* )0;

	//TArray<AActor*> actors, inputs;
	//GetAttachedActors(actors);
	//inputs = actors.FilterByPredicate([](const AActor* a) {
	//	return a->IsA<AFunctionInput>();
	//});

	//TArray<void*> values;
	//for (auto _input : inputs) {
	//	auto input = Cast<AFunctionInput>(_input);
	//	if (input->connectedTo) {
	//		AActor* o = input->connectedTo->GetAttachParentActor();
	//		auto other = Cast<ABlockFunctionPull>(o);
	//		void* v = other->GetValue();
	//		values.Add(v);
	//	}
	//}

	//if (values.Num() < 2) {
	//	value = Maybe<int>::Nothing();
	//	TextComponent->SetText(FString(TEXT("Curried")));
	//	return ( void* )&value;
	//}

	//auto i1 = values[0];
	//auto i2 = values[1];

	//value = Maybe<int>::Just(i1.get());

	//TextComponent->SetText(FString::Format(TEXT("Just {0}"), { i1 }));

	//return ( void* )&value;

}
