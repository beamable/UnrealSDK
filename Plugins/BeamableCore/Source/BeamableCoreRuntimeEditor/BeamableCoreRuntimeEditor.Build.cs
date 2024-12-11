using UnrealBuildTool;

public class BeamableCoreRuntimeEditor : ModuleRules
{
	public BeamableCoreRuntimeEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"BeamableCore",
				"Core",
				"CoreUObject",
				"Engine",
				"Json",
				"JsonUtilities",
				"DeveloperSettings"
			}
		);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
					"EditorSubsystem",
					"EditorStyle",
					"AssetTools"
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Slate",
					"SlateCore",
					"BlueprintGraph",
					"GraphEditor",
					"LevelEditor",
					"PropertyEditor",
					"UMGEditor",
					"Blutility",
					"DeveloperToolSettings",
					"ToolWidgets",
					"EditorScriptingUtilities",
					"Kismet",
					"KismetCompiler",
					"Projects",
					"ToolMenus",
					"ToolMenusEditor",
					"DataTableEditor",
					"HTTP"
				}
			);
		}
	}
}