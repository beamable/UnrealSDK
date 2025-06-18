// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BEAMPROJ_HathoraDemo : ModuleRules
{
	public BEAMPROJ_HathoraDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ApplicationCore",
				"CoreOnline",
				"HathoraSDK"
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			});
		
		// You only need this to access the BeamOSS namespace that has some utility functions for integrating with OnlineSubsystem...
		// If you don't want it, you can simply remove it and do what the utility functions do in your own project.
		// We have this here because we use the UBeamLevelSubsystem --- if you wish to depend only on the OnlineSubsystem stuff in your game code, you can just remove this dependency
		// and make your own UBeamLevelSubsystem-equivalent.
		BeamableUnrealMicroserviceClients.AddMicroserviceClients(this);
		Beam.AddRuntimeModuleDependencies(this);
	}
}
