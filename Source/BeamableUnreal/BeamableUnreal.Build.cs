// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeamableUnreal : ModuleRules
{
	public BeamableUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		Beam.AddRuntimeModuleDependencies(this, true);
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { "HTTP" });
	}
}