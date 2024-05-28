// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;
using System.Collections.Generic;
using System.Linq;
using EpicGames.Core;

public class BeamableUnrealEditorTarget : TargetRules
{
	public BeamableUnrealEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[]
		{
			"BeamableUnreal",
			"BeamableUnrealBlueprintNodes",
			"BeamableUnrealEditor"
		});
		
		var samplePluginName = BeamableUnrealTarget.GetCurrBeamProj(Target);
		EnablePlugins.Add(samplePluginName);
		
		Console.WriteLine($"Configuring editor project as beamproj={samplePluginName}.");
		BeamableUnrealTarget.ConfigureIfSandbox(this, samplePluginName);
		BeamableUnrealTarget.ConfigureIfHathoraDemo(this, samplePluginName);
		BeamableUnrealTarget.ApplyProjectOverrides(Target, samplePluginName);
	}
}