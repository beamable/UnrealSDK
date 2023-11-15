// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BeamableUnrealEditorTarget : TargetRules
{
	public BeamableUnrealEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
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
