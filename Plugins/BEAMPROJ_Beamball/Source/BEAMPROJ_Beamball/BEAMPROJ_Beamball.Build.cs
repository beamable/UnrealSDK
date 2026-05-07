// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
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
				"OnlineServicesEOS",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);

		Beam.AddRuntimeModuleDependencies(this);
		BeamableUnrealMicroserviceClients.AddMicroserviceClients(this);


		// Discord Dependencies
		{
			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				PublicAdditionalLibraries.Add(Path.Combine("$(PluginDir)", "Binaries", "Win64", "discord_game_sdk.dll.lib"));
				RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dll", Path.Combine("$(PluginDir)", "Binaries", "Win64", "discord_game_sdk.dll"));
				RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dll.lib", Path.Combine("$(PluginDir)", "Binaries", "Win64", "discord_game_sdk.dll.lib"));
			}

			if (Target.Platform == UnrealTargetPlatform.Linux)
			{
				PublicAdditionalLibraries.Add(Path.Combine("$(PluginDir)", "Binaries", "Linux", "discord_game_sdk.so"));
				RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.so", Path.Combine("$(PluginDir)", "Binaries", "Linux", "discord_game_sdk.so"));
			}

			if (Target.Platform == UnrealTargetPlatform.Mac)
			{
				PublicAdditionalLibraries.Add(Path.Combine("$(PluginDir)", "Binaries", "Mac", "discord_game_sdk.dylib"));
				RuntimeDependencies.Add("$(TargetOutputDir)/discord_game_sdk.dylib", Path.Combine("$(PluginDir)", "Binaries", "Mac", "discord_game_sdk.dylib"));
			}
		}
	}
}