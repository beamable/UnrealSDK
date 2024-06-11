// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class BeamableUnrealTarget : TargetRules
{
	public const string kCurrentBeamProj = kBeamProj_Sandbox;

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
		ConfigureIfSteamDemo(this, samplePluginName);
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

				HooksEnabled = false,
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

	public const string kBeamProj_SteamDemo = "BEAMPROJ_SteamDemo";

	public static void ConfigureIfSteamDemo(TargetRules TargetRules, string beamProj)
	{
		if (beamProj == kBeamProj_SteamDemo)
		{
			var oss = new Beam.OssConfig()
			{
				IsEnabled = false,

				HooksEnabled = false,
				HookSubsystemImplementation = "",
				HookSubsystemIncludePath = "",

				AdditionalHookModules = Array.Empty<string>(),
			};
			TargetRules.bUsesSteam = true;

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

			if (Directory.Exists(projectPath))
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
				file.CopyTo(targetFilePath, true);
			}

			foreach (DirectoryInfo subDir in dirs)
			{
				string newDestinationDir = Path.Combine(destinationDir, subDir.Name);
				CopyDirectory(subDir.FullName, newDestinationDir);
			}
		}
	}
}

/* BEAMABLE CODE TO COPY PASTE START */

/// <summary>
/// This is a helper class that contains Beamable-owned code to help you configure the Beamable Modules in your project.
/// Any change made to this class will requires you, the game-maker, to manually re-add them when updating Beamable SDK versions.
/// </summary>
public static class Beam
{
	/// <summary>
	/// Struct that describes the options for using the OnlineSubsystemBeamable optional Plugin. If you are not using IOnlineSubsystem in your project, you can ignore this.
	/// </summary>
	public struct OssConfig
	{
		/// <summary>
		/// Whether or not you are using OnlineSubsystemBeamable as the IOnlineSubsystem for your project.
		/// </summary>
		public bool IsEnabled;

		/// <summary>
		/// Whether or not you want to be able to extend functionality of our implementation of the IOnlineSubsystem.
		/// </summary>
		public bool HooksEnabled;

		/// <summary>
		/// The name of a type inheriting from FOnlineSubsystemBeamable (and living in the `Customer` directory of the OnlineSubsystemBeamable package).
		/// </summary>
		public string HookSubsystemImplementation;

		/// <summary>
		/// The include path of the <see cref="HookSubsystemImplementation"/>, relative to the package root (`Customer/MyCustomizedOnlineSubsystemBeamable.h`).
		/// </summary>
		public string HookSubsystemIncludePath;

		/// <summary>
		/// Any additional Modules you'll like to be added to the `Build.cs` file of the OnlineSubsystemBeamable module.
		/// The primary case for this is adding third-party SDKs you wish to integrate with Beamable (Discord, Hathora, etc...).
		/// </summary>
		public string[] AdditionalHookModules;
	}


	/// <summary>
	/// This is built by <see cref="Beam.ConfigureGame"/> (and others), so we can pass information down to each of the projects `Build.cs` files through <see cref="TargetRules.AdditionalData"/>.
	/// See <see cref="Beam.GetOrAddAdditionalData{T}"/> and <see cref="Beam.GetAdditionalData{T}"/>.
	/// </summary>
	public class BeamableAdditionalData
	{
		/// <summary>
		/// Maps to <see cref="OssConfig.AdditionalHookModules"/>.
		/// </summary>
		public string[] OssAdditionalModules = Array.Empty<string>();
	}


	/// <summary>
	/// Call this function in your Editor.Target.cs file (passing in itself) to ensure that your editor Target is correctly set up to compile the Beamable modules.
	/// </summary>
	/// <param name="TargetRules">The YourProjectEditor's TargetRules.</param>
	/// <param name="OssConfig">Your project's <see cref="OssConfig"/>.</param>
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
			"BeamableCoreRuntimeEditor",
			"BeamableCoreEditor",

			"Json",
			"JsonUtilities",
		});
	}

	/// <summary>
	/// Call this function in your Server.Target.cs file (passing in itself) to ensure that your dedicated server Target is correctly set up to compile the Beamable modules.
	/// </summary>
	/// <param name="TargetRules">The YourProjectServer's TargetRules.</param>
	/// <param name="OssConfig">Your project's <see cref="OssConfig"/>.</param>
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

	/// <summary>
	/// Call this function in your .Target.cs file (passing in itself) to ensure that your standalone game client Target is correctly set up to compile the Beamable modules.
	/// </summary>
	/// <param name="TargetRules">The YourProject's TargetRules.</param>
	/// <param name="OssConfig">Your project's <see cref="OssConfig"/>.</param>
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
	/// Call this function any non-editor/uncooked-only Module's Build.cs file to add Beamable as a dependency to that module.
	/// </summary>
	/// <param name="ModuleRules">The Module's ModuleRules.</param>
	/// <param name="bIsPrivate">Whether you want this to be a Private/Public dependency.</param>
	public static void AddRuntimeModuleDependencies(ModuleRules ModuleRules, bool bIsPrivate = false)
	{
		var l = bIsPrivate ? ModuleRules.PrivateDependencyModuleNames : ModuleRules.PublicDependencyModuleNames;
		l.AddRange(new[]
		{
			"BeamableCore",
			"BeamableCoreRuntime",

			"Json",
			"JsonUtilities",
		});

		if (ModuleRules.Target.bBuildEditor)
			l.Add("BeamableCoreRuntimeEditor");
	}

	/// <summary>
	/// Call this function any uncooked-only Module's Build.cs file to add Beamable as a dependency to that module.
	/// </summary>
	/// <param name="ModuleRules">The Module's ModuleRules.</param>
	/// <param name="bIsPrivate">Whether you want this to be a Private/Public dependency.</param>
	public static void AddUncookedOnlyModuleDependencies(ModuleRules ModuleRules, bool bIsPrivate = false)
	{
		var l = bIsPrivate ? ModuleRules.PrivateDependencyModuleNames : ModuleRules.PublicDependencyModuleNames;
		l.AddRange(new[]
		{
			"BeamableCore",
			"BeamableCoreBlueprintNodes",
			"BeamableCoreRuntime",

			"Json",
			"JsonUtilities",
		});

		if (ModuleRules.Target.bBuildEditor)
			l.Add("BeamableCoreRuntimeEditor");
	}

	/// <summary>
	/// Call this function any editor-only Module's Build.cs file to add Beamable as a dependency to that module.
	/// </summary>
	/// <param name="ModuleRules">The Module's ModuleRules.</param>
	/// <param name="bIsPrivate">Whether you want this to be a Private/Public dependency.</param>
	public static void AddEditorModuleDependencies(ModuleRules ModuleRules, bool bIsPrivate = false)
	{
		var l = bIsPrivate ? ModuleRules.PrivateDependencyModuleNames : ModuleRules.PublicDependencyModuleNames;
		l.AddRange(new[]
		{
			"BeamableCore",
			"BeamableCoreBlueprintNodes",
			"BeamableCoreRuntime",
			"BeamableCoreRuntimeEditor",
			"BeamableCoreEditor",

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

	/// <summary>
	/// Adds some defines that might be generally useful.
	/// </summary>
	private static void AddUtilityMacros(TargetRules TargetRules)
	{
		TargetRules.ProjectDefinitions.Add("BEAM_STRINGIFY(X)=#X");
	}
}

/* BEAMABLE CODE TO COPY PASTE END */
