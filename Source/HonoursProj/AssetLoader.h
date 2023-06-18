

#pragma once

#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Engine/DataTable.h"


struct FResource_Material {
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> White;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Blue;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Orange;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Grey;
		FResource_Material()
		:	White(TEXT("/Game/Puzzle/Meshes/WhiteMaterial.WhiteMaterial"))
		,	Blue(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
		,	Orange(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		,	Grey(TEXT("/Game/Puzzle/Meshes/GreyMaterial.GreyMaterial"))
		{}
};
static FResource_Material ResourceInst_Material;

struct FResource_Mesh {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PuzzleCube;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Cylinder;
		FResource_Mesh()
		:	PuzzleCube(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
		,	Cylinder(TEXT("/Game/MyContent/Meshes/Cylinder.Cylinder"))
		{}
};
static FResource_Mesh ResourceInst_Mesh;

struct FResource_Data {
		ConstructorHelpers::FObjectFinderOptional<UDataTable> TypesTable;
		FResource_Data()
		:	TypesTable(TEXT("DataTable'/Game/MyContent/Data/Tbl_Types.Tbl_Types'"))
		{}
};
static FResource_Data ResourceInst_Data;



struct FAssets {
		FResource_Material Material;
		FResource_Mesh Mesh;
		FResource_Data Data;
		FAssets()
		:	Material(ResourceInst_Material)
		,	Mesh(ResourceInst_Mesh)
		,	Data(ResourceInst_Data)
		{}
};
static FAssets Assets;




