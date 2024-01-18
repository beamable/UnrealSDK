// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealEditorTarget : TargetRules
{
	public BeamableUnrealEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[]
		{
			"BeamableUnreal",
			"BeamableUnrealBlueprintNodes",
			
			"BeamableCore",
			"BeamableCoreBlueprintNodes",
			"BeamableCoreEditor",
			
			"Json",
			"JsonUtilities"
		});		
	}
}
