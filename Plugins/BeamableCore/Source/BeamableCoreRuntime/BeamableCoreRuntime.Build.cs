using System;
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
				"CoreUObject",
				"Engine",
				"InputCore",
				"HeadMountedDisplay",
				"Json",
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

		// Is UBT building for Editor ?
		if (Target.bCompileAgainstEditor)
		{
			Console.WriteLine("BeamableCoreRuntime - Adding Necessary Editor Modules");
			
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"Engine",
					"CoreUObject",
					"UnrealEd",
					"SlateCore",
					"Slate",
					"EditorStyle",
					"Kismet",
					"KismetCompiler",
					"Projects", // Required to use IPluginManager in order to configure new Slate styles
					"ToolMenus",
					"ToolMenusEditor",
					"UMGEditor",
					"DeveloperSettings",
					"EditorSubsystem",
					"Json",
					"JsonUtilities",
					"DataTableEditor",
					"DeveloperToolSettings",
					"AssetTools",
					"BeamableCoreRuntimeEditor",
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"CoreUObject",
					"Engine",
					"Slate",
					"SlateCore",
					"BlueprintGraph",
					"GraphEditor",
					"LevelEditor",
					"PropertyEditor",
					"UMGEditor",
					"Blutility",
					"DeveloperToolSettings",
					"UnrealEd",
					"ToolWidgets",
					"EditorScriptingUtilities",
					"Json",
					"JsonUtilities",
					"HTTP",
				}
			);
		}
	}
}