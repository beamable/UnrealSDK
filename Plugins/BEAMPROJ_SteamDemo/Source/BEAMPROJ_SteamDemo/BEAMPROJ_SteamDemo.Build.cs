// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class BEAMPROJ_SteamDemo : ModuleRules
{
	public BEAMPROJ_SteamDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
				"Steamworks"
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

		BeamableUnrealMicroserviceClients.AddMicroserviceClients(this);
		Beam.AddRuntimeModuleDependencies(this);
	}
}
