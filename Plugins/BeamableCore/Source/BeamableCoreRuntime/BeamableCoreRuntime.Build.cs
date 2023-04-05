using UnrealBuildTool;

public class BeamableCoreRuntime : ModuleRules
{
	public BeamableCoreRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"BeamableCore",
				"Core",
				"CoreUObject", "Engine", "InputCore",
				"HeadMountedDisplay", "Json", 
				"JsonUtilities",
				"DeveloperSettings",
				"HTTP"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			}
		);
	}
}