// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

using UnrealBuildTool;

public partial class OnlineSubsystemBeamable : ModuleRules
{
	private partial void CustomerExtension(ReadOnlyTargetRules Target);
	
	public OnlineSubsystemBeamable(ReadOnlyTargetRules Target) : base(Target)
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
			
		if (Target.bCompileAgainstEngine)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Engine",
					"CoreOnline",
				}
			);

			PublicDependencyModuleNames.AddRange(
				new string[] {
					"OnlineSubsystemUtils"
				}
			);
		}
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"OnlineSubsystem",
				"OnlineBase",
				"OnlineSubsystemUtils",
				"DeveloperSettings",
				"BeamableCore", 
				"BeamableCoreRuntime",
				"Json",
				"JsonUtilities",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"Sockets",
				"SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
				}
			);
		}


		var additionalData = Target.GetAdditionalData<Beam.BeamableAdditionalData>();
		PublicDependencyModuleNames.AddRange(additionalData.OssAdditionalModules);
		CustomerExtension(Target);
	}
}
