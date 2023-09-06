// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HonoursProj : ModuleRules
{
	public HonoursProj(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivatePCHHeaderFile = "HonoursProjPCH.h";

        PublicIncludePaths.AddRange(
        new string[] {
            "HonoursProj"
        });

        //PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //GeneratedCodeVersion = 
        bLegacyPublicIncludePaths = false;
        //	BuildVersion
        PCHUsage = PCHUsageMode.NoSharedPCHs;
        CppStandard = CppStandardVersion.Cpp17;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", 
			"CoreUObject",
			"Engine", 
            "InputCore",
			"HeadMountedDisplay",
            "UMG", 
            "LevelSequence",
            "MovieScene",
			"Slate", 
			"SlateCore"
		});

        if (Target.bBuildEditor)
        {
            PublicDependencyModuleNames.AddRange(new string[] {
				"UnrealEd"
			});
        }
    }
}
