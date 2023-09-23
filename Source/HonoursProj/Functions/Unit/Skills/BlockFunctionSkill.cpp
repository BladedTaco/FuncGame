// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/Unit/Skills/BlockFunctionSkill.h"

ABlockFunctionSkill::ABlockFunctionSkill() {

}


bool ABlockFunctionSkill::TrySkill() const {
	if (IsValid(Unit)) {
		UStatusBarComponent* StatusBar = NULL;
		switch (StatusType) {
		case EStatusType::HEALTH: StatusBar = Unit->Health; break;
		case EStatusType::MANA: StatusBar = Unit->Mana; break;
		case EStatusType::STAMINA: StatusBar = Unit->Stamina; break;
		default: break;
		}
		
		if (IsValid(StatusBar)) {
			if (StatusBar->CurrentValue > StatusCost) {
				StatusBar->CurrentValue -= StatusCost;
				return true;
			}
		}
	}
	return false;
}