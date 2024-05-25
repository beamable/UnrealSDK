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
		bOverrideBuildEnvironment = true;
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
		ApplyProjectOverrides(Target, samplePluginName);
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
			var oss = new Beam.OssConfig()
			{
				IsEnabled = false,

				HooksEnabled = false,
				HookSubsystemImplementation = "",
				HookSubsystemIncludePath = "",

				AdditionalHookModules = Array.Empty<string>(),
			};

			if (TargetRules.Type == UnrealBuildTool.TargetType.Game)
			{
				Beam.ConfigureGame(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Editor)
			{
				Beam.ConfigureEditor(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Server)
			{
				Beam.ConfigureServer(TargetRules, oss);
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
			var oss = new Beam.OssConfig()
			{
				IsEnabled = true,

				HooksEnabled = true,
				HookSubsystemImplementation = "FOnlineSubsystemHathoraDemo",
				HookSubsystemIncludePath = "Customer/OnlineSubsystemHathoraDemo.h",

				AdditionalHookModules = new[] { "HathoraSDK", "DiscordSDK" }
			};

			if (TargetRules.Type == UnrealBuildTool.TargetType.Game)
			{
				Beam.ConfigureGame(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Editor)
			{
				Beam.ConfigureEditor(TargetRules, oss);
			}
			else if (TargetRules.Type == UnrealBuildTool.TargetType.Server)
			{
				Beam.ConfigureServer(TargetRules, oss);
			}
			else
			{
				throw new ArgumentOutOfRangeException();
			}
		}
	}

	public static void ApplyProjectOverrides(TargetInfo Target, string beamProj)
	{
		var overrideFolders = new[] { "Config", ".beamable/content" };
		
		foreach (var overrideFolder in overrideFolders)
		{
			var projRoot = Target.ProjectFile.Directory.ToDirectoryInfo().ToString();
			var projectPath = Path.Combine(projRoot, overrideFolder);
			var overridesPath = Path.Combine(projRoot, "Plugins", beamProj, "Overrides", overrideFolder);
			if (!Directory.Exists(overridesPath))
			{
				Console.WriteLine($"{beamProj} project does not have Overrides directory for this expected override path. Create one at: {overridesPath}");
				return;
			}	
			
			if(Directory.Exists(projectPath))
				Directory.Delete(projectPath, true);
			
			CopyDirectory(overridesPath, projectPath);
		}

		static void CopyDirectory(string sourceDir, string destinationDir)
		{
			// Get information about the source directory
			var dir = new DirectoryInfo(sourceDir);

			// Check if the source directory exists
			if (!dir.Exists)
				throw new DirectoryNotFoundException($"Source directory not found: {dir.FullName}");

			// Cache directories before we start copying
			DirectoryInfo[] dirs = dir.GetDirectories();

			// Create the destination directory
			Directory.CreateDirectory(destinationDir);

			// Get the files in the source directory and copy to the destination directory
			foreach (FileInfo file in dir.GetFiles())
			{
				string targetFilePath = Path.Combine(destinationDir, file.Name);
				file.CopyTo(targetFilePath,true);
			}

			foreach (DirectoryInfo subDir in dirs)
			{
				string newDestinationDir = Path.Combine(destinationDir, subDir.Name);
				CopyDirectory(subDir.FullName, newDestinationDir);
			}
		}
	}
}

/// BEAMABLE CODE TO COPY PASTE START
public static class Beam
{
	public struct OssConfig
	{
		public bool IsEnabled;
		public bool HooksEnabled;
		public string HookSubsystemImplementation;
		public string HookSubsystemIncludePath;
		public string[] AdditionalHookModules;
	}


	public class BeamableAdditionalData
	{
		public string[] OssAdditionalModules = Array.Empty<string>();
	}


	public static void ConfigureEditor(TargetRules TargetRules, OssConfig OssConfig)
	{
		var additionalData = GetOrAddAdditionalData<BeamableAdditionalData>(TargetRules);
		AddUtilityMacros(TargetRules);
		ConfigOnlineSubsystem(TargetRules, OssConfig, additionalData);

		TargetRules.ExtraModuleNames.AddRange(new[]
		{
			"BeamableCore",
			"BeamableCoreBlueprintNodes",
			"BeamableCoreRuntime",
			"BeamableCoreEditor",

			"Json",
			"JsonUtilities",
		});
	}

	public static void ConfigureServer(TargetRules TargetRules, OssConfig OssConfig)
	{
		var additionalData = GetOrAddAdditionalData<BeamableAdditionalData>(TargetRules);
		AddUtilityMacros(TargetRules);
		ConfigOnlineSubsystem(TargetRules, OssConfig, additionalData);

		TargetRules.ExtraModuleNames.AddRange(new[]
		{
			"BeamableCore",
			"BeamableCoreRuntime",

			"Json",
			"JsonUtilities",
		});
	}

	public static void ConfigureGame(TargetRules TargetRules, OssConfig OssConfig)
	{
		var additionalData = GetOrAddAdditionalData<BeamableAdditionalData>(TargetRules);
		AddUtilityMacros(TargetRules);
		ConfigOnlineSubsystem(TargetRules, OssConfig, additionalData);

		TargetRules.ExtraModuleNames.AddRange(new[]
		{
			"BeamableCore",
			"BeamableCoreRuntime",

			"Json",
			"JsonUtilities",
		});
	}


	/// <summary>
	/// To be used in Target.cs files to add objects to <see cref="TargetRules.AdditionalData"/> in order to be used by various Build.cs files.
	/// </summary>
	public static T GetOrAddAdditionalData<T>(TargetRules TargetRules) where T : class, new()
	{
		TargetRules.AdditionalData ??= new Dictionary<Type, object>();

		var dict = TargetRules.AdditionalData as Dictionary<Type, object>;
		dict!.TryAdd(typeof(T), new T());
		return dict[typeof(T)] as T;
	}

	/// <summary>
	/// To be used in Build.cs files to read objects added to the <see cref="TargetRules.AdditionalData"/> by <see cref="GetOrAddAdditionalData{T}"/>.
	/// </summary>
	public static T GetAdditionalData<T>(this ReadOnlyTargetRules TargetRules) where T : class, new()
	{
		if (TargetRules.AdditionalData is Dictionary<Type, object> dictionary)
		{
			if (dictionary.TryGetValue(typeof(T), out var data))
				return data as T;

			throw new Exception(
				$"Failed to find an additional data with the given type {typeof(T).Name}.\n" +
				"Make sure you call GetOrAddAdditionalData<T> from your Target.cs file passing in the correct Type.\n");
		}

		throw new Exception(
			"Using beamable requires the AdditionalData to be a Dictionary of Type/Object.\n" +
			"We provide a utility function that allows you to add your own additional data next to beamable's own BeamableAdditionalData.\n" +
			"We do this because the Beamable plugin needs some additional data but we didn't want to lock you out of passing in your own things.");
	}


	/// <summary>
	/// Configures the Beamable SDK to work with UE's Online Subsystem stuff.
	/// </summary>
	private static void ConfigOnlineSubsystem(TargetRules TargetRules, OssConfig OssConfig, BeamableAdditionalData AdditionalData)
	{
		// Don't do anything to configure OSS if its not enabled
		if (!OssConfig.IsEnabled) return;

		// Include the OnlineSubsystem modules in the target.
		TargetRules.ExtraModuleNames.AddRange(new[]
		{
			"OnlineSubsystem",
			"OnlineSubsystemUtils",
			"OnlineSubsystemBeamable"
		});

		// If we are building the editor, we also add the OnlineSubsystemBeamableBp module (which is where your BeamFlow nodes for Microservices live when OSS is enabled) 
		if (TargetRules.bBuildEditor)
		{
			TargetRules.ExtraModuleNames.AddRange(new[]
			{
				"OnlineSubsystemBeamableBp" // TODO: Make sure this module exists before doing this.
			});
		}

		// Add the ENABLE OSS define so that the BeamableCore plugins can declare some utilities for when it is working with OSS
		TargetRules.ProjectDefinitions.Add("BEAM_ENABLE_BEAMABLE_OSS=1");

		// If OSS Hooks are enabled, the customer can pass in the Hook entry point implementation and we'll auto-configure it for them.
		if (OssConfig.HooksEnabled)
		{
			TargetRules.ProjectDefinitions.Add("BEAM_ENABLE_OSS_HOOKS=1");
			TargetRules.ProjectDefinitions.Add($"BEAM_OSS_SUBSYSTEM_IMPLEMENTATION={OssConfig.HookSubsystemImplementation}");
			TargetRules.ProjectDefinitions.Add($"BEAM_OSS_SUBSYSTEM_INCLUDE=BEAM_STRINGIFY({OssConfig.HookSubsystemIncludePath})");

			// Pass down, to the OnlineSubsystemBeamable plugin, a list of Module names that it'll also depend on 
			AdditionalData.OssAdditionalModules = OssConfig.AdditionalHookModules;
		}
	}

	private static void AddUtilityMacros(TargetRules TargetRules)
	{
		TargetRules.ProjectDefinitions.Add("BEAM_STRINGIFY(X)=#X");
	}
}
/// BEAMABLE CODE TO COPY PASTE END
