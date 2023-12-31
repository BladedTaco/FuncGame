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
#include "Components/WidgetComponent.h"


struct FResource_Material {
		ConstructorHelpers::FObjectFinderOptional<UMaterial> Base;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> Font;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> PostProcess;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> Shiny;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Black;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Blood;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Blue;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Brown;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Copper;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> DarkGrey;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Gold;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Green;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Grey;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Orange;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Pink;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Purple;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Red;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RoyalPurple;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Silver;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Turquoise;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Void;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> White;
		FResource_Material()
		:	Base(TEXT("Material'/Game/MyContent/Materials/BaseMaterial.BaseMaterial'"))
		,	Font(TEXT("Material'/Game/MyContent/Materials/FontMaterial.FontMaterial'"))
		,	PostProcess(TEXT("Material'/Game/MyContent/Materials/PostProcessMaterial.PostProcessMaterial'"))
		,	Shiny(TEXT("Material'/Game/MyContent/Materials/ShinyMaterial.ShinyMaterial'"))
		,	Black(TEXT("/Game/MyContent/Materials/BlackMaterial.BlackMaterial"))
		,	Blood(TEXT("/Game/MyContent/Materials/BloodMaterial.BloodMaterial"))
		,	Blue(TEXT("/Game/MyContent/Materials/BlueMaterial.BlueMaterial"))
		,	Brown(TEXT("/Game/MyContent/Materials/BrownMaterial.BrownMaterial"))
		,	Copper(TEXT("/Game/MyContent/Materials/CopperMaterial.CopperMaterial"))
		,	DarkGrey(TEXT("/Game/MyContent/Materials/DarkGreyMaterial.DarkGreyMaterial"))
		,	Gold(TEXT("/Game/MyContent/Materials/GoldMaterial.GoldMaterial"))
		,	Green(TEXT("/Game/MyContent/Materials/GreenMaterial.GreenMaterial"))
		,	Grey(TEXT("/Game/MyContent/Materials/GreyMaterial.GreyMaterial"))
		,	Orange(TEXT("/Game/MyContent/Materials/OrangeMaterial.OrangeMaterial"))
		,	Pink(TEXT("/Game/MyContent/Materials/PinkMaterial.PinkMaterial"))
		,	Purple(TEXT("/Game/MyContent/Materials/PurpleMaterial.PurpleMaterial"))
		,	Red(TEXT("/Game/MyContent/Materials/RedMaterial.RedMaterial"))
		,	RoyalPurple(TEXT("/Game/MyContent/Materials/RoyalPurpleMaterial.RoyalPurpleMaterial"))
		,	Silver(TEXT("/Game/MyContent/Materials/SilverMaterial.SilverMaterial"))
		,	Turquoise(TEXT("/Game/MyContent/Materials/TurquoiseMaterial.TurquoiseMaterial"))
		,	Void(TEXT("/Game/MyContent/Materials/VoidMaterial.VoidMaterial"))
		,	White(TEXT("/Game/MyContent/Materials/WhiteMaterial.WhiteMaterial"))
		{}
};

struct FResource_Mesh {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PuzzleCube;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> OffsetCylinder;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Cylinder;
		FResource_Mesh()
		:	PuzzleCube(TEXT("/Game/MyContent/Meshes/PuzzleCube.PuzzleCube"))
		,	OffsetCylinder(TEXT("/Game/MyContent/Meshes/offsetCylinder.OffsetCylinder"))
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
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Counter;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Dice;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Ordinal;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Maybe;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Call;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> OrdinalFunc;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Position;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Stamina;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mana;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Health;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> LiftA2;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Abs;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Minus;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Plus;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PositionAdd;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Sign;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Times;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Shield;
		FResource_Icon()
		:	Percentage(TEXT("StaticMesh'/Game/MyContent/Meshes/percent.percent'"))
		,	Counter(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Counter.Counter'"))
		,	Dice(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/d20.d20'"))
		,	Ordinal(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/ordinal.ordinal'"))
		,	Maybe(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/maybe.maybe'"))
		,	Call(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Call.Call'"))
		,	OrdinalFunc(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/OrdinalIcon.OrdinalIcon'"))
		,	Position(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Position.Position'"))
		,	Stamina(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Stamina.Stamina'"))
		,	Mana(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Mana.Mana'"))
		,	Health(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Health.Health'"))
		,	LiftA2(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/LiftA2.LiftA2'"))
		,	Abs(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Abs.Abs'"))
		,	Minus(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Minus.Minus'"))
		,	Plus(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Plus.Plus'"))
		,	PositionAdd(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/PositionAdd.PositionAdd'"))
		,	Sign(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Sign.Sign'"))
		,	Times(TEXT("StaticMesh'/Game/MyContent/Meshes/Functions/Times.Times'"))
		,	Shield(TEXT("StaticMesh'/Game/MyContent/Meshes/Shielder.Shielder'"))
		{}
};

struct FResource_TypeIcon {
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Applicative;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Bool;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Bounded;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Chain;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Char;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Int;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Either;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Enum;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Foldable;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Functor;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Key;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> List;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Lock;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Maybe;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mirror;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Monad;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Ordinal;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Percent;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Show;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Template;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Traversable;
		FResource_TypeIcon()
		:	Applicative(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Applicative.Applicative'"))
		,	Bool(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/bool.bool'"))
		,	Bounded(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Bounded.Bounded'"))
		,	Chain(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Chain.Chain'"))
		,	Char(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/char.char'"))
		,	Int(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/d20.d20'"))
		,	Either(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Either.Either'"))
		,	Enum(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Enum.Enum'"))
		,	Foldable(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Foldable.Foldable'"))
		,	Functor(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/functor.functor'"))
		,	Key(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/key.key'"))
		,	List(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/List.List'"))
		,	Lock(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/lock.lock'"))
		,	Maybe(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/maybe.maybe'"))
		,	Mirror(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Mirror.Mirror'"))
		,	Monad(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Monad.Monad'"))
		,	Ordinal(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/ordinal.ordinal'"))
		,	Percent(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/percent.percent'"))
		,	Show(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/show.show'"))
		,	Template(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/template.template'"))
		,	Traversable(TEXT("StaticMesh'/Game/MyContent/Meshes/Types/Traversable.Traversable'"))
		{}
};

struct FResource_HUD {
		ConstructorHelpers::FClassFinder<UUserWidget> Function;
		ConstructorHelpers::FClassFinder<UUserWidget> Parameter;
		ConstructorHelpers::FClassFinder<UWidgetComponent> ASH;
		FResource_HUD()
		:	Function(TEXT("/Game/MyContent/Blueprints/HUD_Function"))
		,	Parameter(TEXT("/Game/MyContent/Blueprints/HUD_Parameter"))
		,	ASH(TEXT("/Game/MyContent/Blueprints/BP_AutoScalingHUD"))
		{}
};

struct FResource_TypeRepr {
		ConstructorHelpers::FClassFinder<AActor> Applicative;
		ConstructorHelpers::FClassFinder<AActor> Bool;
		ConstructorHelpers::FClassFinder<AActor> Bounded;
		ConstructorHelpers::FClassFinder<AActor> Char;
		ConstructorHelpers::FClassFinder<AActor> Either;
		ConstructorHelpers::FClassFinder<AActor> Enum;
		ConstructorHelpers::FClassFinder<AActor> Eq;
		ConstructorHelpers::FClassFinder<AActor> Float;
		ConstructorHelpers::FClassFinder<AActor> Foldable;
		ConstructorHelpers::FClassFinder<AActor> Function;
		ConstructorHelpers::FClassFinder<AActor> Functor;
		ConstructorHelpers::FClassFinder<AActor> Int;
		ConstructorHelpers::FClassFinder<AActor> List;
		ConstructorHelpers::FClassFinder<AActor> Maybe;
		ConstructorHelpers::FClassFinder<AActor> Monad;
		ConstructorHelpers::FClassFinder<AActor> Monoid;
		ConstructorHelpers::FClassFinder<AActor> Number;
		ConstructorHelpers::FClassFinder<AActor> Ordinal;
		ConstructorHelpers::FClassFinder<AActor> Semigroup;
		ConstructorHelpers::FClassFinder<AActor> Show;
		ConstructorHelpers::FClassFinder<AActor> Template;
		ConstructorHelpers::FClassFinder<AActor> Traversable;
		FResource_TypeRepr()
		:	Applicative(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Applicative"))
		,	Bool(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Bool"))
		,	Bounded(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Bounded"))
		,	Char(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Char"))
		,	Either(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Either"))
		,	Enum(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Enum"))
		,	Eq(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Eq"))
		,	Float(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Float"))
		,	Foldable(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Foldable"))
		,	Function(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Function"))
		,	Functor(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Functor"))
		,	Int(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Int"))
		,	List(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_List"))
		,	Maybe(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Maybe"))
		,	Monad(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Monad"))
		,	Monoid(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Monoid"))
		,	Number(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Number"))
		,	Ordinal(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Ordinal"))
		,	Semigroup(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Semigroup"))
		,	Show(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Show"))
		,	Template(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Template"))
		,	Traversable(TEXT("/Game/MyContent/Blueprints/Types/TypeRepr_Traversable"))
		{}
};



struct FAssets {
		FResource_Material Material;
		FResource_Mesh Mesh;
		FResource_Data Data;
		FResource_Icon Icon;
		FResource_TypeIcon TypeIcon;
		FResource_HUD HUD;
		FResource_TypeRepr TypeRepr;
		FAssets()
		:	Material({})
		,	Mesh({})
		,	Data({})
		,	Icon({})
		,	TypeIcon({})
		,	HUD({})
		,	TypeRepr({})
		{}
};

FAssets* Assets();
