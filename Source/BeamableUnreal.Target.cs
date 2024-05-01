// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class BeamableUnrealTarget : TargetRules
{
	public const string kCurrentBeamProj = kBeamProj_HathoraDemo;
	
	public BeamableUnrealTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[]
		{
			"BeamableUnreal",
		});

		var samplePluginName = GetCurrBeamProj(Target);
		EnablePlugins.Add(samplePluginName);

		Console.WriteLine($"Configuring standalone project as beamproj={samplePluginName}.");
		ConfigureIfSandbox(this, samplePluginName);
		ConfigureIfHathoraDemo(this, samplePluginName);
	}
	
	public static string GetCurrBeamProj(TargetInfo Target)
	{
		string samplePluginName = kCurrentBeamProj;

		
		var samplePluginOverrideFile = Path.Combine(Target.ProjectFile.Directory.ToDirectoryInfo().ToString(), "BeamProjOverride.txt");
		Console.WriteLine($"Looking for 'BeamProjOverride.txt' at '{samplePluginOverrideFile}'.");
		if (File.Exists(samplePluginOverrideFile))
		{
			var overrideBeamProj = File.ReadAllText(samplePluginOverrideFile).Trim();
			Console.WriteLine($"Found plugin override file. Swapping beamproj={samplePluginName} for override={overrideBeamProj}.");
			samplePluginName = overrideBeamProj;
		}

		return samplePluginName;
	}
	
	public const string kBeamProj_Sandbox = "BEAMPROJ_Sandbox";

	public static void ConfigureIfSandbox(TargetRules TargetRules, string beamProj)
	{
		if (beamProj == kBeamProj_Sandbox)
		{
			var oss = new BeamableModuleUtils.OssConfig()
			{
				IsEnabled = false,

				HooksEnabled = false,
				HookSubsystemImplementation = "",
				HookSubsystemIncludePath = "",

				AdditionalHookModules = Array.Empty<string>(),
			};

			if (TargetRules.Type == UnrealBuildTool.TargetType.Game)
			{
				BeamableModuleUtils.ConfigureGame(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Editor)
			{
				BeamableModuleUtils.ConfigureEditor(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Server)
			{
				BeamableModuleUtils.ConfigureServer(TargetRules, oss);
			}
			else
			{
				throw new ArgumentOutOfRangeException();
			}
		}
	}

	public const string kBeamProj_HathoraDemo = "BEAMPROJ_HathoraDemo";

	public static void ConfigureIfHathoraDemo(TargetRules TargetRules, string beamProj)
	{
		if (beamProj == kBeamProj_HathoraDemo)
		{
			var oss = new BeamableModuleUtils.OssConfig()
			{
				IsEnabled = true,

				HooksEnabled = true,
				HookSubsystemImplementation = "FOnlineSubsystemHathoraDemo",
				HookSubsystemIncludePath = "Customer/OnlineSubsystemHathoraDemo.h",

				AdditionalHookModules = new[] { "HathoraSDK", "DiscordSDK" }
			};

			if (TargetRules.Type == UnrealBuildTool.TargetType.Game)
			{
				BeamableModuleUtils.ConfigureGame(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Editor)
			{
				BeamableModuleUtils.ConfigureEditor(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Server)
			{
				BeamableModuleUtils.ConfigureServer(TargetRules, oss);
			}
			else
			{
				throw new ArgumentOutOfRangeException();
			}
		}
	}
}