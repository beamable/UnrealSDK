// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using UnrealBuildTool;

public class BeamableCore : ModuleRules
{
	public BeamableCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);


		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "InputCore",
				"HeadMountedDisplay", "Json", "JsonUtilities", "HTTP",
				"DeveloperSettings", "GameplayTags", "WebSockets"
				// ... add other public dependencies that you statically link with here ...
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"OnlineSubsystem"
				// ... add private dependencies that you statically link with here ...	
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}

public static class BeamableModuleUtils
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
				"OnlineSubsystemBeamableBp"
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