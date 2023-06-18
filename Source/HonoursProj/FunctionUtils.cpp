// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionUtils.h"

#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
//
//#include "Components/StaticMeshComponent.h"
//#include "Engine/StaticMesh.h"
//#include "Materials/MaterialInstance.h"
//#include "Materials/Material.h"



UTypeHandler::UTypeHandler() {
	// Structure to hold one-time initialization
	struct FConstructorStatics {
		ConstructorHelpers::FObjectFinderOptional<UDataTable> TypeTable;
		FConstructorStatics()
			: TypeTable(TEXT("DataTable'/Game/MyContent/Data/Tbl_Types.Tbl_Types'"))
		{}
	};
	static FConstructorStatics ConstructorStatics;


}