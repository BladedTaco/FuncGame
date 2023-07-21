// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HonoursProjEditorTarget : TargetRules
{
    public HonoursProjEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("HonoursProj");
		ExtraModuleNames.Add("DetailsCustomizer");
	}
}
