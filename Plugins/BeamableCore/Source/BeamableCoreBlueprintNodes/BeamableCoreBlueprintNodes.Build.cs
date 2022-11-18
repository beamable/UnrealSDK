using UnrealBuildTool;

public class BeamableCoreBlueprintNodes : ModuleRules
{
	public BeamableCoreBlueprintNodes(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"CoreUObject",
				"BeamableCore",
				"BeamableCoreRuntime",
				"UnrealEd",
				"BlueprintGraph",
				"GraphEditor",
				"PropertyEditor",
				"SlateCore",
				"Slate",
				"EditorStyle",
				"Kismet",
				"KismetCompiler",
				"Projects", // Required to use IPluginManager in order to configure new Slate styles
				"ToolMenus",
				"ToolMenusEditor", 
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