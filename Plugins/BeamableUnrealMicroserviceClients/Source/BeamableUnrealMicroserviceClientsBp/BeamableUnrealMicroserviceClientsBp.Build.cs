// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BeamableUnrealMicroserviceClientsBp : ModuleRules
{
	public BeamableUnrealMicroserviceClientsBp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"BeamableUnrealMicroserviceClients",

				"BeamableCore",
                "BeamableCoreRuntime",
                "BeamableCoreBlueprintNodes",
                
                "BlueprintGraph",
			});


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",					
			});
	}

	public static void AddMicroserviceClientsBp(ModuleRules Rules)
	{
		Rules.PublicDependencyModuleNames.AddRange(new[] { "BeamableUnrealMicroserviceClientsBp" });
	}
	
}