// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TextHUD.h"

void UTextWidget::SetText(FString NewText) {
	if (auto tHUD = Cast<UTextHUD>(GetUserWidgetObject())) {
		tHUD->Text = NewText;
	}
}