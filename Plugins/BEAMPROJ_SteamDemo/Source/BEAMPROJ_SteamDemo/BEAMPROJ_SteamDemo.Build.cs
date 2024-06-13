// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class BEAMPROJ_SteamDemo : ModuleRules
{
	public BEAMPROJ_SteamDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"BeamableCore",
				"BeamableCoreRuntime",
				"OnlineSubsystem",
				"OnlineSubsystemBeamable",
				"OnlineSubsystemUtils",
				"OnlineSubsystemSteam",
				"Steamworks"
			}
		);        
		// string SteamPath = Path.Combine(EngineDirectory, "Source/ThirdParty/Steamworks", "Steamv153");
		// SteamPath = Path.Combine(SteamPath, "sdk/public");
		// Console.WriteLine(SteamPath);
		// PublicIncludePaths.Add(SteamPath);

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
	}
}
