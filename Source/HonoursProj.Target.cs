// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HonoursProjTarget : TargetRules
{
    public HonoursProjTarget(TargetInfo Target) : base(Target)
	{
        DefaultBuildSettings = BuildSettingsVersion.V2;
        Type = TargetType.Game;
		ExtraModuleNames.Add("HonoursProj");
	}
}
