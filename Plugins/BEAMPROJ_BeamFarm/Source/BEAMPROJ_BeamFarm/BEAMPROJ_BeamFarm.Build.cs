// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BEAMPROJ_BeamFarm : ModuleRules
{
	public BEAMPROJ_BeamFarm(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "OnlineSubsystem",
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
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		// Add the generic Online Subsystem to project
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystemUtils" });
		
		// Dynamically add Google Online Subsystem for platforms where you intend to use it
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemGoogle");
		}

		if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemIOS");
		}
		if (Target.Platform == UnrealTargetPlatform.IOS ||
		    Target.Platform == UnrealTargetPlatform.Mac)
		{
			DynamicallyLoadedModuleNames.Add("OnlineSubsystemApple");
		}
	}
}
