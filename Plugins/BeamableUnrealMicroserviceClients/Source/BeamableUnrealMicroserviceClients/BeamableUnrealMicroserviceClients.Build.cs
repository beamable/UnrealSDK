// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeamableUnrealMicroserviceClients : ModuleRules
{
	public BeamableUnrealMicroserviceClients(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"BeamableCore",
				"BeamableCoreRuntime",

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

	public static void AddMicroserviceClients(ModuleRules Rules)
	{
		Rules.PublicDependencyModuleNames.AddRange(new[] { "BeamableUnrealMicroserviceClients" });
	}
	
}