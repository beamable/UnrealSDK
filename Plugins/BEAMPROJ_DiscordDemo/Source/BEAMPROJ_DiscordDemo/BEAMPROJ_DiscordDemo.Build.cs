// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BEAMPROJ_DiscordDemo : ModuleRules
{
	public BEAMPROJ_DiscordDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DiscordSDK",
				
				// Because we are making microservice calls, we add the microservice plugin for our project
				"BeamableUnrealMicroserviceClients"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		Beam.AddRuntimeModuleDependencies(this);
	}
}