using UnrealBuildTool;

public class BeamableUnrealEditor : ModuleRules
{
	public BeamableUnrealEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DirectoryWatcher",

				"BeamableCore",
				"BeamableCoreRuntimeEditor",
				"BeamableCoreEditor",
				"UnrealEd",
				"Projects"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);
	}
}