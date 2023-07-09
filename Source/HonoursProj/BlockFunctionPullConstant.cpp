// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockFunctionPullConstant.h"

#include "Components/TextRenderComponent.h"

void* ABlockFunctionPullConstant::GetValue() {
	TextComponent->SetText(FText::FromString(FString::Format(TEXT("{0}"), { value })));

	numValue = Number<int>(value);
	return (void*)&numValue;
}
