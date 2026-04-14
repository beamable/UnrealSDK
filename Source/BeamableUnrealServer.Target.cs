using System;
using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealServerTarget : TargetRules
{
	public BeamableUnrealServerTarget(TargetInfo Target) : base(Target)
	{
		bOverrideBuildEnvironment = true;
		bUseLoggingInShipping = true;
		bUseChecksInShipping = false;
		bBuildWithEditorOnlyData = false;
		bUsesSlate = false;
		bCompileCEF3 = false;

		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;


		// Only include the core and necessary modules for the server build
		ExtraModuleNames.AddRange(new string[]
		{
			"BeamableUnreal",
			// Server specific modules can be added here
			"OnlineSubsystem", // If using any online subsystem
			"OnlineSubsystemUtils",
		});

		var samplePluginName = BeamableUnrealTarget.GetCurrBeamProj(Target);

		Console.WriteLine($"Configuring server project as beamproj={samplePluginName}.");
		BeamableUnrealTarget.ConfigureIfBeamball(this, samplePluginName);
		BeamableUnrealTarget.ConfigureIfBeamFarm(this, samplePluginName);
		BeamableUnrealTarget.ConfigureIfLiveOpsDemo(this, samplePluginName);
		BeamableUnrealTarget.ConfigureIfDiscordDemo(this, samplePluginName);

	}
}