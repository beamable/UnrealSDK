using System;
using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealServerTarget : TargetRules
{
	public BeamableUnrealServerTarget(TargetInfo Target) : base(Target)
	{
		bOverrideBuildEnvironment = true;
		if (Target.Platform != UnrealTargetPlatform.Linux && IsSelfBuiltUnrealEngine())
		{
			BuildEnvironment = TargetBuildEnvironment.Unique;
		}
		bUseLoggingInShipping = true;
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		bUsesSteam = false; // Set to true if using Steam

		// Only include the core and necessary modules for the server build
		ExtraModuleNames.AddRange(new string[]
		{
			"BeamableUnreal",
			// Server specific modules can be added here
			"OnlineSubsystem", // If using any online subsystem
			"OnlineSubsystemUtils",
		});

		var samplePluginName = BeamableUnrealTarget.GetCurrBeamProj(Target);
		EnablePlugins.Add(samplePluginName);

		Console.WriteLine($"Configuring server project as beamproj={samplePluginName}.");
		BeamableUnrealTarget.ConfigureIfSandbox(this, samplePluginName);
		BeamableUnrealTarget.ConfigureIfHathoraDemo(this, samplePluginName);
		BeamableUnrealTarget.ApplyProjectOverrides(Target, samplePluginName);
	}
	
    private static bool IsSelfBuiltUnrealEngine()
    {
        // Unreal.EngineSourceDirectory points to the Engine/Source directory
        string engineSourceDirectory = UnrealBuildBase.Unreal.EngineSourceDirectory.FullName;
        string buildVersionFilePath = Path.Combine(engineSourceDirectory, "Runtime", "Launch", "Resources", "Version.h");

        // Check if Version.h file exists, indicating a self-built Unreal Engine
        return File.Exists(buildVersionFilePath);
    }
}