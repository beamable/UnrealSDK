// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CustomReplacementTypes : ModuleRules
{
	public CustomReplacementTypes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"BeamableCore",
				"BeamableCoreRuntime",
				"GameplayTags",

				"Json",
				"JsonUtilities",
			});


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",					
			});
	}
	
}