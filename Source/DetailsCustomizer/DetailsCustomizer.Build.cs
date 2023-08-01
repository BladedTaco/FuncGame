// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DetailsCustomizer : ModuleRules
{
	public DetailsCustomizer (ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp17;

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"DetailsCustomizer/Public"
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				"DetailsCustomizer/Private"
            }
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
            {
                "Core",
                "CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "PropertyEditor",
				"EditorStyle",
                "EditorWidgets",
				// ... add private dependencies that you statically link with here ...
			}
			);



        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				// ... add other public dependencies that you statically link with here ...
				"CoreUObject",
                "Engine",
                "InputCore",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "PropertyEditor",
                "HonoursProj",
            }
            );

        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
