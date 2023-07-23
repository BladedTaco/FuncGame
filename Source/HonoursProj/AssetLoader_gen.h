﻿// ---------------------------------------------------------------------------------------
// This File (AssetLoader_gen.h) is automatically generated by Types.tt using T4 Text Transformer
// ANY changes made to this file directly are liable to be overwritten on compile
// If this file needs to be edited, Types.tt will need to be extended in its functionality
// ---------------------------- Start AutoGenerated File ---------------------------------
#pragma once

#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"


struct FResource_Material {
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> White;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Blue;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Orange;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Grey;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Pink;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Red;
		FResource_Material()
		:	White(TEXT("/Game/Puzzle/Meshes/WhiteMaterial.WhiteMaterial"))
		,	Blue(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
		,	Orange(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		,	Grey(TEXT("/Game/Puzzle/Meshes/GreyMaterial.GreyMaterial"))
		,	Pink(TEXT("/Game/Puzzle/Meshes/PinkMaterial.PinkMaterial"))
		,	Red(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"))
		{}
};

struct FResource_Mesh {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PuzzleCube;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Cylinder;
		FResource_Mesh()
		:	PuzzleCube(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
		,	Cylinder(TEXT("/Game/MyContent/Meshes/Cylinder.Cylinder"))
		{}
};

struct FResource_Data {
		ConstructorHelpers::FObjectFinderOptional<UDataTable> TypesTable;
		FResource_Data()
		:	TypesTable(TEXT("DataTable'/Game/MyContent/Data/Tbl_Types.Tbl_Types'"))
		{}
};

struct FResource_Icon {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Percentage;
		FResource_Icon()
		:	Percentage(TEXT("StaticMesh'/Game/MyContent/Meshes/percent.percent'"))
		{}
};

struct FResource_HUD {
		ConstructorHelpers::FClassFinder<UUserWidget> Function;
		ConstructorHelpers::FClassFinder<UUserWidget> Parameter;
		FResource_HUD()
		:	Function(TEXT("/Game/MyContent/Blueprints/HUD_Function"))
		,	Parameter(TEXT("/Game/MyContent/Blueprints/HUD_Parameter"))
		{}
};



struct FAssets {
		FResource_Material Material;
		FResource_Mesh Mesh;
		FResource_Data Data;
		FResource_Icon Icon;
		FResource_HUD HUD;
		FAssets()
		:	Material({})
		,	Mesh({})
		,	Data({})
		,	Icon({})
		,	HUD({})
		{}
};

FAssets* Assets();
