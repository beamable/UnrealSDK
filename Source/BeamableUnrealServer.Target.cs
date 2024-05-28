using System;
using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealServerTarget : TargetRules
{
	public BeamableUnrealServerTarget(TargetInfo Target) : base(Target)
	{
		bOverrideBuildEnvironment = true;

		if (IsSelfBuiltUnrealEngine())
		{
			BuildEnvironment = TargetBuildEnvironment.Unique;
			bUseLoggingInShipping = true;
		}
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


    private bool IsSelfBuiltUnrealEngine()
    {
        // Read environment variable that indicates a self-built Unreal Engine
        string selfBuiltEnvVar = Environment.GetEnvironmentVariable("UE_SELF_BUILT");

        // Check if the environment variable is set to "1"
        bool isSelfBuilt = !string.IsNullOrEmpty(selfBuiltEnvVar) && selfBuiltEnvVar == "1";

        return isSelfBuilt;
    }
}