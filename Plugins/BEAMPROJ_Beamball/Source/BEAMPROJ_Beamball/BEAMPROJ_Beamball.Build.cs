// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BEAMPROJ_Beamball : ModuleRules
{
	public BEAMPROJ_Beamball(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				// Dependencies for Steam
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
				"OnlineSubsystemSteam",
				"Steamworks",

				// We'll need to use microservices from this module
				"BeamableUnrealMicroserviceClients",
				"HTTP",

				// Dependencies for EOS plugin
				"CoreOnline",
				"OnlineServicesInterface",
				"OnlineServicesEOS"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...
			}
		);

		Beam.AddRuntimeModuleDependencies(this);
		BeamableUnrealMicroserviceClients.AddMicroserviceClients(this);
	}
}