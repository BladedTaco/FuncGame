// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionUtils.h"

#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
//
//#include "Components/StaticMeshComponent.h"
//#include "Engine/StaticMesh.h"
//#include "Materials/MaterialInstance.h"
//#include "Materials/Material.h"


#include "AssetLoader.h"

UTypeHandler::UTypeHandler() {
	UDataTable* types = Assets.Data.TypesTable.Get();


}