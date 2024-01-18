// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealTarget : TargetRules
{
	public BeamableUnrealTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange(new string[]
		{
			"BeamableUnreal", 
			
			"BeamableCore",
			"BeamableCoreRuntime",
			
			"Json",
			"JsonUtilities"
		});
	}
}