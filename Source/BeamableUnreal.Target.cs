// Copyright Epic Games, Inc. All Rights Reserved.

/* BEAMABLE USINGS TO COPY PASTE START */

using System;
/* BEAMABLE USINGS TO COPY PASTE END */
using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;
using EpicGames.Core;

public class BeamableUnrealTarget : TargetRules
{
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
		Console.WriteLine($"Configuring standalone project as beamproj={samplePluginName}.");

		ConfigureIfSandbox(this, samplePluginName);
		ConfigureIfLiveOpsDemo(this, samplePluginName);
		ConfigureIfHathoraDemo(this, samplePluginName);
		ConfigureIfSteamDemo(this, samplePluginName);
		ConfigureIfDiscordDemo(this, samplePluginName);
	}

	public static string GetCurrBeamProj(TargetInfo Target)
	{
		var uproject = File.ReadAllText(Target.ProjectFile.FullName);
		var uprojectJson = JsonObject.Parse(uproject);
		var plugins = uprojectJson.GetObjectArrayField("Plugins");
		foreach (var p in plugins)
		{
			var name = p.GetStringField("Name");
			if (name.StartsWith("BEAMPROJ_"))
			{
				Console.WriteLine($"Checking {name} to see if this is the currently selected sample.");
				if (p.GetBoolField("Enabled"))
				{
					Console.WriteLine($"Sample {name} is the currently selected sample");
					return name;
				}
			}
		}

		return kBeamProj_Sandbox;
	}

	public const string kBeamProj_Sandbox = "BEAMPROJ_Sandbox";

	public static void ConfigureIfSandbox(TargetRules TargetRules, string beamProj)
	{
		if (beamProj == kBeamProj_Sandbox)
		{
			var oss = Beam.OssConfig.Disabled();

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

	public const string kBeamProj_LiveOpsDemo = "BEAMPROJ_LiveOpsDemo";

	public static void ConfigureIfLiveOpsDemo(TargetRules TargetRules, string beamProj)
	{
		if (beamProj == kBeamProj_LiveOpsDemo)
		{
			var oss = Beam.OssConfig.Disabled();

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
			var oss = Beam.OssConfig.Disabled();
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

	public const string kBeamProj_DiscordDemo = "BEAMPROJ_DiscordDemo";

	public static void ConfigureIfDiscordDemo(TargetRules TargetRules, string beamProj)
	{
		if (beamProj == kBeamProj_DiscordDemo)
		{
			var oss = Beam.OssConfig.Disabled();

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

		public static OssConfig Disabled()
		{
			return new OssConfig()
			{
				IsEnabled = false,
				HooksEnabled = false,
				HookSubsystemImplementation = string.Empty,
				HookSubsystemIncludePath = string.Empty,
				AdditionalHookModules = Array.Empty<string>()
			};
		}
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
		Console.WriteLine($"Beamable - Ran ConfigureEditor - With OSS: {OssConfig.IsEnabled}");
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
		Console.WriteLine($"Beamable - Ran ConfigureServer - With OSS: {OssConfig.IsEnabled}");
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
		Console.WriteLine($"Beamable - Ran ConfigureGame - With OSS: {OssConfig.IsEnabled}");
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

		if (ModuleRules.Target.bCompileAgainstEditor)
		{
			Console.WriteLine($"Beamable - Adding Runtime Editor From Runtime Module");
			l.Add("BeamableCoreRuntimeEditor");
		}
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

		if (ModuleRules.Target.bCompileAgainstEditor)
		{
			Console.WriteLine($"Beamable - Adding Runtime Editor From Runtime Module");
			l.Add("BeamableCoreRuntimeEditor");
		}
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
		// Don't do anything to configure OSS if it is not enabled
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
		else
		{
			TargetRules.ProjectDefinitions.Add("BEAM_ENABLE_OSS_HOOKS=0");
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